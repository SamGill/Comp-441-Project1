// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.cpp v1.0

#include "bandit.h"
#include "desperado.h"
#include <random>
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;


//=============================================================================
// default constructor
//=============================================================================
Bandit::Bandit() : Entity()
{
	banditSpeed = 60;
	spriteData.width = banditNS::WIDTH;           // size of Ship1
	spriteData.height = banditNS::HEIGHT;
	spriteData.x = banditNS::X;                   // location on screen
	spriteData.y = banditNS::Y;
	spriteData.rect.bottom = banditNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = banditNS::WIDTH;
	velocity.x = BANDIT_SPEED;                             // velocity X
	velocity.y = BANDIT_SPEED;                             // velocity Y
	//frameDelay = banditNS::SHIP_ANIMATION_DELAY;
	//startFrame = banditNS::SHIP1_START_FRAME;     // first frame of ship animation
	//endFrame     = banditNS::SHIP1_END_FRAME;     // last frame of ship animation
	//currentFrame = startFrame;
	radius = banditNS::WIDTH/2.0;

	mass = banditNS::MASS;

	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Bandit::initialize(Game *gamePtr, int width, int height, int ncols,
						TextureManager *textureM)
{

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

bool Bandit::initializeBullet(Game* gamePtr, TextureManager *textureM)
{
	return (banditBullet.initialize(gamePtr, bulletNS::WIDTH,bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, textureM));
}

//=============================================================================
// draw the bandit
//=============================================================================
void Bandit::draw()
{
	Image::draw();              // draw bandit
	banditBullet.draw();
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Bandit::update(float frameTime)
{
	Entity::update(frameTime);
	//spriteData.angle += frameTime * banditNS::ROTATION_RATE;  // rotate the ship
	//spriteData.x += frameTime * velocity.x;         // move ship along X 

	//spriteData.y += frameTime * banditNS::SPEED;         // move ship along Y
	spriteData.y += frameTime * banditSpeed;

	banditBullet.banditUpdate(frameTime);
	
}


void Bandit::chance_to_shoot() 
{

	if (banditBullet.getVisible() == false && visible)
	{
		random_device rd;   
		mt19937 gen(rd());  
		uniform_int_distribution<> dist(1,FRAME_RATE * 60);
		uniform_int_distribution<> leftOrRight(0,1);

		if (dist(gen) < 10)
		{
			banditBullet.setVisible(true);

			banditBullet.setY(spriteData.y + banditNS::HEIGHT/2);
			//0 means left, else right
			if (leftOrRight(gen) == 0)
				banditBullet.setX(spriteData.x + banditNS::WIDTH/4);
			else 
				banditBullet.setX(spriteData.x + banditNS::WIDTH - (5 * banditNS::WIDTH/16)); 
		}
	}
}

Bullet Bandit::getBullet() 
{
	return banditBullet;
}

void Bandit::removeBullet()
{
	banditBullet.setVisible(false);
	banditBullet.setY(0);
}

void Bandit::setSpeed(float newSpeed)
{
	banditSpeed = newSpeed;
}

//=============================================================================
// damage
//=============================================================================
//void Bandit::damage(WEAPON weapon)
//{
//    shieldOn = true;
//}

