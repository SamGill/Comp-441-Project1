// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Move spaceship with arrow keys.
// Chapter 5 Desperado.cpp v1.0
// This class is the core of the game

#include "desperado.h"
#include <string>
#include <sstream>
#include <time.h>
#include <stdlib.h>

//Just for testing
int banditCounter = 10;
int banditPlaceCount = 0;
int score = 0;
//int waveNum = 1;
int delay = 0;
bool gameOverCond = false;
bool victoryCond = false;
bool outOfHearts = false;
bool outOfGold = false;
bool infoSeen = false;

bool endSound = false;
bool winSound = false;

float banditSpeedScreen = 1.0f;

void subtractHeart(Image hearts[])
{
	for (int i = HEART_NUMBER - 1; i >= 0; i--)
	{
		if (hearts[i].getVisible())
		{
			hearts[i].setVisible(false);
			if (i == 0)
				outOfHearts = true;
			return;
		}
	}
}

void subtractGold(Image gold[])
{
	for (int i = GOLD_NUMBER - 1; i >= 0; i--)
	{
		if (gold[i].getVisible())
		{

			gold[i].setVisible(false);
			if (i == 0)
				outOfGold = true;
			return;
		}
	}
}


//=============================================================================
// Constructor
//=============================================================================
Desperado::Desperado()
{}

//=============================================================================
// Destructor
//=============================================================================
Desperado::~Desperado()
{
	releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Desperado::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError

	srand(time(NULL));

	waveNum = 1;

	scoreFont = new TextDX();
	wave = new TextDX();
	victory = new TextDX();
	gameOver = new TextDX();
	enemySpeed = new TextDX();

	audio = new Audio();
	 // init sound system
    audio = new Audio();

    if (*WAVE_BANK != '\0' && *SOUND_BANK != '\0')  // if sound files defined
    {
        if( FAILED( hr = audio->initialize() ) )
        {
            if( hr == HRESULT_FROM_WIN32( ERROR_FILE_NOT_FOUND ) )
                throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize sound system because media file not found."));
            else
                throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize sound system."));
        }
    }

	//Initialize the game text
	if(scoreFont->initialize(graphics, 32, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing output font"));
	if(enemySpeed->initialize(graphics, 24, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing output font"));
	if(wave->initialize(graphics, 32, true, false, "Rockwell Extra Bold") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing output font"));
	if(victory->initialize(graphics, 50, true, false, "Broadway") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing output font"));
	if(gameOver->initialize(graphics, 50, true, false, "Broadway") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing output font"));

	scoreFont->setFontColor(graphicsNS::RED);
	wave->setFontColor(graphicsNS::BLACK);
	victory->setFontColor(graphicsNS::YELLOW);
	gameOver->setFontColor(graphicsNS::RED);
	enemySpeed->setFontColor(graphicsNS::BLACK);

	

	if (!cactusTexture.initialize(graphics,CACTUS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cactus texture"));
	if (!backgroundTexture.initialize(graphics, BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

	

	if (!playerTexture.initialize(graphics, PLAYER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player texture"));

	if (!bulletTexture.initialize(graphics, BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));

	if (!heartTexture.initialize(graphics, HEART_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing heart texture"));

	if (!goldTexture.initialize(graphics, GOLD_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gold texture"));

	if (!banditTexture.initialize(graphics, BANDIT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bandit texture"));

	if (!infoTexture.initialize(graphics, INFO_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing info texture"));


	// cactus
	if (!cactus.initialize(graphics,0,0,0, &cactusTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cactus"));
	cactus.setX(GAME_WIDTH/4);
	cactus.setY(GAME_HEIGHT/4);

	if (!playerBullet.initialize(this,0,0,0, &bulletTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
	playerBullet.setVisible(false);

	for (int i = 0; i < HEART_NUMBER; i++) 
	{
		if (!hearts[i].initialize(graphics,0,0,0, &heartTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing a heart"));
		hearts[i].setX((hearts[i].getWidth() + PIXEL_SPACE)* i);
		//hearts[i].setY(0);
	}

	for (int i = 0; i < GOLD_NUMBER; i++) 
	{
		if (!golds[i].initialize(graphics,0,0,0, &goldTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing a gold"));
		golds[i].setX(GAME_WIDTH - ((golds[i].getWidth() + PIXEL_SPACE) * (i + 1)));
	}


	//Many bandits
	for (int i = 0; i < MAX_BANDITS; i++) 
	{
		if (!manyBandits[i].initialize(this,0,0,0, &banditTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing a bandit"));
		if (!manyBandits[i].initializeBullet(this, &bulletTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing a bandit bullet"));

		manyBandits[i].setX((manyBandits[i].getWidth() + PIXEL_SPACE)* i);
	}



	// background 
	if (!background.initialize(graphics,GAME_WIDTH,GAME_HEIGHT,0, &backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));

	if (!player.initialize(this, 0,0,0,&playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));
	player.setY(GAME_HEIGHT - player.getHeight());
	player.setX(GAME_WIDTH/2);

	//Info
	if (!info.initialize(graphics,800,600,0, &infoTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing info"));

	info.setX(100);
	info.setY(100);

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Desperado::update()
{

	if(input->anyKeyPressed())
	{
		infoSeen = true;
		info.setVisible(false);
	}

	//Displays info first, then starts game
	if(infoSeen && !gameOverCond && !victoryCond)
	{
		if (outOfGold || outOfHearts)
		{
			for(int i = 0; i < MAX_BANDITS; i++)
			{

				manyBandits[i].chance_to_shoot();
				
				//manyBandits[i].setY(manyBandits[i].getY() + frameTime * banditNS::SPEED);
				manyBandits[i].update(frameTime);

				if (manyBandits[i].getY() > GAME_HEIGHT && manyBandits[i].getVisible())
				{
					manyBandits[i].setVisible(false);
					banditCounter--;
				}

			}
			return;
		}

		banditPlaceCount++;

		int placement;
		placement = rand() % (GAME_WIDTH - bandit.getWidth());

		if(banditCounter <= 0 && !manyBandits[0].getVisible() && !manyBandits[1].getVisible()
			&& !manyBandits[2].getVisible() && !manyBandits[3].getVisible() && !manyBandits[4].getVisible())
		{
			delay++;
			if(delay == waveDelay && waveNum < 5)
			{
				waveNum++; //Moves to next wave

				//Checks which wave it is and sets bandit count accordingly
				if(waveNum == 2)
				{
					banditCounter = 5;
				}
				else if(waveNum == 3)
				{
					banditSpeedScreen = 1.5;
					banditCounter = 5;
					for (int i = 0; i < MAX_BANDITS; i++)
					{
						manyBandits[i].setSpeed(90);
					}
				}
				else if(waveNum == 4)
					banditCounter = 5;
				else if(waveNum == 5)
				{
					banditSpeedScreen = 2.0;
					banditCounter = 5;
					for (int i = 0; i < MAX_BANDITS; i++)
					{
						manyBandits[i].setSpeed(120);
					}
				}
				delay = 0;

				//Display bandits in a line again
				for (int i = 0; i < MAX_BANDITS; i++)
				{
					if(!manyBandits[i].getVisible())
					{
						manyBandits[i].setVisible(true);
						manyBandits[i].setY(-100);
						manyBandits[i].setX((i+1)*manyBandits[i].getWidth());
					}
				}
			}
		}


		if(input->isKeyDown(VK_RIGHT))            // if move right
		{
			player.setX(player.getX() + frameTime * PLAYER_SPEED);

			int playerRightBorder = GAME_WIDTH - player.getWidth(); 
			if (player.getX() > playerRightBorder)               // if off screen right
				player.setX(playerRightBorder);     // position off screen left
		}
		if(input->isKeyDown(VK_LEFT))             // if move left
		{
			player.setX(player.getX() - frameTime * PLAYER_SPEED);
			if (player.getX() < 0)         // if off screen left
				player.setX(0);           // position off screen right
		}

		//If "Z" key is pressed, left gun shoots
		if(input->isKeyDown(0x5A) && playerBullet.getVisible() == false) 
		{
			playerBullet.setVisible(true);
			playerBullet.setX(player.getX() + 21);
			playerBullet.setY(player.getY());

			//Play gun sounds
			audio->playCue(GUNSHOT);
		}

		//If "X" key is pressed, right gun shoots
		if(input->isKeyDown(0x58) && playerBullet.getVisible() == false) 
		{
			playerBullet.setVisible(true);
			playerBullet.setX(player.getX() + 99);
			playerBullet.setY(player.getY());
			//Play gun sounds
			audio->playCue(GUNSHOT);
		}

		if (banditCounter > 0)
		{
			for (int i = 0; i < MAX_BANDITS; i++)
			{
				if(banditCounter % 1000 && !manyBandits[i].getVisible())
				{
					manyBandits[i].setVisible(true);
					manyBandits[i].setY(-100);
					manyBandits[i].setX(placement);
				}
			}
		}
		//Move all the bandits test
		for(int i = 0; i < MAX_BANDITS; i++)
		{
			//Checks if bandit is visible first
			if(manyBandits[i].getVisible())
			{
				manyBandits[i].chance_to_shoot();
			}
			//manyBandits[i].setY(manyBandits[i].getY() + frameTime * banditNS::SPEED);
			manyBandits[i].update(frameTime);

			if (manyBandits[i].getY() > GAME_HEIGHT && manyBandits[i].getVisible())
			{
				manyBandits[i].setVisible(false);
				banditCounter--;
				subtractGold(golds);
				audio->playCue(STOLEN);
			}

		}
		playerBullet.update(frameTime);
		player.update(frameTime);

	}

	//Checks for game over condition
	if(gameOverCond)
	{
		if(!endSound)
			audio->playCue(FAILURE);
		endSound = true;
		Sleep(1000);
		if(input->anyKeyPressed())
			exitGame();
	}

	//Checks for victory condition
	if(victoryCond && !outOfGold)
	{
		if(!winSound)
			audio->playCue(VICTORY);
		winSound = true;
		//victoryCond = false;
		Sleep(1000);
		if(input->anyKeyPressed())
			exitGame();
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Desperado::ai()
{

}

//=============================================================================
// Handle collisions
//=============================================================================
void Desperado::collisions()
{
	VECTOR2 collisionVector;


	for (int i = 0; i < MAX_BANDITS; i++)
	{
		if (manyBandits[i].collidesWith(playerBullet,collisionVector) && playerBullet.getVisible() && manyBandits[i].getVisible())
		{
			manyBandits[i].setVisible(false);
			playerBullet.setVisible(false);
			banditCounter--;
			score++;
		}

		if (manyBandits[i].getBullet().collidesWith(player,collisionVector) && manyBandits[i].getBullet().getVisible())
		{
			manyBandits[i].removeBullet();

			subtractHeart(hearts);
			score -= 5;

			audio->playCue(OUCH);
		}
	}

	
}

//=============================================================================
// Render game items
//=============================================================================
void Desperado::render()
{

	//Score display
	std::stringstream scoreDisplay;
	scoreDisplay << "Score: ";
	scoreDisplay << score;

	//Wave display
	std::stringstream waveDisplay;
	waveDisplay << "Wave: ";
	waveDisplay << waveNum;

	//Victory text
	std::stringstream victoryDisplay;
	victoryDisplay << "VICTORY!!!";

	//Game over text
	std::stringstream gameOverDisplay;

	//Bandit speed display
	std::stringstream banditSpeedDisplay;

	banditSpeedDisplay << "Bandit Speed: ";
	banditSpeedDisplay << banditSpeedScreen;

	if (outOfGold)
		gameOverDisplay << "All your gold was stolen!";
	else if (outOfHearts)
		gameOverDisplay << "You died!";

	gameOverDisplay << "\n\tGAME OVER";

	graphics->spriteBegin();                // begin drawing sprites

	
	background.draw();
	

	cactus.draw();
	//bandit.draw();

	for (int i = 0; i < MAX_BANDITS; i++)
	{
		manyBandits[i].draw();
	}

	playerBullet.draw();

	for (int i = 0; i < HEART_NUMBER; i++)
		hearts[i].draw();

	for (int i = 0; i < GOLD_NUMBER; i++)
		golds[i].draw();

	scoreFont->print(scoreDisplay.str(), GAME_WIDTH - 175, 40); //Displays score
	wave->print(waveDisplay.str(), GAME_WIDTH/2 - 30, 30); //Displays wave
	enemySpeed->print(banditSpeedDisplay.str(), GAME_WIDTH - 175, 80);

	if(waveNum == 5 && !manyBandits[0].getVisible() && !manyBandits[1].getVisible()
		&& !manyBandits[2].getVisible() && !manyBandits[3].getVisible() && !manyBandits[4].getVisible() && !manyBandits[5].getVisible()
		&& !manyBandits[6].getVisible())
	{
		victory->print(victoryDisplay.str(), GAME_WIDTH/2 - 50, GAME_HEIGHT/2 - 50);
		victoryCond = true;
	}

	if (outOfGold || outOfHearts)
	{
		gameOver->print(gameOverDisplay.str(), GAME_WIDTH/2 - 100, GAME_HEIGHT/2 - 100);
		gameOverCond = true;
	}
	else
		player.draw();


	info.draw();
	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Desperado::releaseAll()
{
	cactusTexture.onLostDevice();
	infoTexture.onLostDevice();
	banditTexture.onLostDevice();
	backgroundTexture.onLostDevice();
	bulletTexture.onLostDevice();
	goldTexture.onLostDevice();
	heartTexture.onLostDevice();
	playerTexture.onLostDevice();

	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Desperado::resetAll()
{
	cactusTexture.onResetDevice();
	infoTexture.onResetDevice();
	banditTexture.onResetDevice();
	backgroundTexture.onResetDevice();
	bulletTexture.onResetDevice();
	goldTexture.onResetDevice();
	heartTexture.onResetDevice();
	playerTexture.onResetDevice();

	Game::resetAll();
	return;
}
