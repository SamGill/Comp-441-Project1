// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.cpp v1.0

#include "bullet.h"

//=============================================================================
// default constructor
//=============================================================================
Bullet::Bullet() : Entity()
{
    spriteData.width = bulletNS::WIDTH;           // size of Ship1
    spriteData.height = bulletNS::HEIGHT;
    spriteData.x = bulletNS::X;                   // location on screen
    spriteData.y = bulletNS::Y;
    spriteData.rect.bottom = bulletNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = bulletNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    //frameDelay = bulletNS::SHIP_ANIMATION_DELAY;
    //startFrame = bulletNS::SHIP1_START_FRAME;     // first frame of ship animation
    //endFrame     = bulletNS::SHIP1_END_FRAME;     // last frame of ship animation
    //currentFrame = startFrame;
    radius = bulletNS::WIDTH/2.0;

	mass = bulletNS::MASS;
    
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Bullet::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Bullet::draw()
{
    Image::draw();              // draw ship
    
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Bullet::update(float frameTime)
{
    Entity::update(frameTime);
    //spriteData.angle += frameTime * bulletNS::ROTATION_RATE;  // rotate the ship
    spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y
   
   
}

//=============================================================================
// damage
//=============================================================================
//void Bullet::damage(WEAPON weapon)
//{
//    shieldOn = true;
//}

