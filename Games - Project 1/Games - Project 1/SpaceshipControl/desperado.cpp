// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Move spaceship with arrow keys.
// Chapter 5 Desperado.cpp v1.0
// This class is the core of the game

#include "desperado.h"
#include <string>
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

#pragma region Built_in_textures 
    // nebula texture
    if (!nebulaTexture.initialize(graphics,NEBULA_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

    // planet texture
    if (!planetTexture.initialize(graphics,PLANET_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

    // spaceship texture
    if (!shipTexture.initialize(graphics,SHIP_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship texture"));
#pragma endregion 

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

#pragma region Built_in_initializations 
    // nebula
    if (!nebula.initialize(graphics,0,0,0,&nebulaTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

    // planet
    if (!planet.initialize(graphics,0,0,0,&planetTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));
    // place planet in center of screen
    planet.setX(GAME_WIDTH*0.5f  - planet.getWidth()*0.5f);
    planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);

    // ship
    if (!ship.initialize(graphics,SHIP_WIDTH, SHIP_HEIGHT, SHIP_COLS, &shipTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));
    ship.setX(GAME_WIDTH/4);                    // start above and left of planet
    ship.setY(GAME_HEIGHT/4);
    ship.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);   // animation frames
    ship.setCurrentFrame(SHIP_START_FRAME);     // starting frame
    ship.setFrameDelay(SHIP_ANIMATION_DELAY);
#pragma endregion

	// cactus
	if (!cactus.initialize(graphics,0,0,0, &cactusTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cactus"));
	cactus.setX(GAME_WIDTH/4);
	cactus.setY(GAME_HEIGHT/4);
	
	if (!playerBullet.initialize(graphics,0,0,0, &bulletTexture))
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

	// background 
	if (!background.initialize(graphics,GAME_WIDTH,GAME_HEIGHT,0, &backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));

	if (!player.initialize(graphics, 0,0,0,&playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));
	player.setY(GAME_HEIGHT - player.getHeight());
	player.setX(GAME_WIDTH/2);

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Desperado::update()
{
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
	}

	//If "X" key is pressed, right gun shoots
	if(input->isKeyDown(0x58) && playerBullet.getVisible() == false) 
	{
		playerBullet.setVisible(true);
		playerBullet.setX(player.getX() + 99);
		playerBullet.setY(player.getY());
	}

	if (playerBullet.getVisible()) 
		playerBullet.setY(playerBullet.getY() - frameTime * BULLET_SPEED);

	if (playerBullet.getY() < 0)
		playerBullet.setVisible(false);

	playerBullet.update(frameTime);
    player.update(frameTime);
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Desperado::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Desperado::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void Desperado::render()
{
    graphics->spriteBegin();                // begin drawing sprites

	background.draw();
    
	cactus.draw();
	player.draw();

	
	playerBullet.draw();
	for (int i = 0; i < HEART_NUMBER; i++)
		hearts[i].draw();

	for (int i = 0; i < GOLD_NUMBER; i++)
		golds[i].draw();

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Desperado::releaseAll()
{
    shipTexture.onLostDevice();
    planetTexture.onLostDevice();
    nebulaTexture.onLostDevice();
	cactusTexture.onLostDevice();

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
    nebulaTexture.onResetDevice();
    planetTexture.onResetDevice();
    shipTexture.onResetDevice();
	cactusTexture.onResetDevice();

	banditTexture.onResetDevice();
	backgroundTexture.onResetDevice();
	bulletTexture.onResetDevice();
	goldTexture.onResetDevice();
	heartTexture.onResetDevice();
	playerTexture.onResetDevice();



    Game::resetAll();
    return;
}
