// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.cpp v1.0

#include "player.h"

//=============================================================================
// default constructor
//=============================================================================
Player::Player() : Entity()
{
    spriteData.width = playerNS::WIDTH;           // size of Ship1
    spriteData.height = playerNS::HEIGHT;
    spriteData.x = playerNS::X;                   // location on screen
    spriteData.y = playerNS::Y;
    spriteData.rect.bottom = playerNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = playerNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    //frameDelay = playerNS::SHIP_ANIMATION_DELAY;
    //startFrame = playerNS::SHIP1_START_FRAME;     // first frame of ship animation
    //endFrame     = playerNS::SHIP1_END_FRAME;     // last frame of ship animation
    //currentFrame = startFrame;
    radius = playerNS::WIDTH/2.0;

	mass = playerNS::MASS;
    
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Player::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Player::draw()
{
    Image::draw();              // draw ship
    
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Player::update(float frameTime)
{
    Entity::update(frameTime);
    //spriteData.angle += frameTime * playerNS::ROTATION_RATE;  // rotate the ship
    spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y
   
   
}

//=============================================================================
// damage
//=============================================================================
void Player::damage(WEAPON weapon)
{
	if (weapon == BANDIT){}
		//do Subtract Gold
	if (weapon == BULLET){}
		//subtract a heart
}

