// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.cpp v1.0

#include "bandit.h"

//=============================================================================
// default constructor
//=============================================================================
Bandit::Bandit() : Entity()
{
    spriteData.width = banditNS::WIDTH;           // size of Ship1
    spriteData.height = banditNS::HEIGHT;
    spriteData.x = banditNS::X;                   // location on screen
    spriteData.y = banditNS::Y;
    spriteData.rect.bottom = banditNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = banditNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
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

//=============================================================================
// draw the ship
//=============================================================================
void Bandit::draw()
{
    Image::draw();              // draw ship
    
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
    spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y

    // Bounce off walls
    if (spriteData.x > GAME_WIDTH-banditNS::WIDTH)    // if hit right screen edge
    {
        spriteData.x = GAME_WIDTH-banditNS::WIDTH;    // position at right screen edge
        velocity.x = -velocity.x;                   // reverse X direction
    } else if (spriteData.x < 0)                    // else if hit left screen edge
    {
        spriteData.x = 0;                           // position at left screen edge
        velocity.x = -velocity.x;                   // reverse X direction
    }
    if (spriteData.y > GAME_HEIGHT-banditNS::HEIGHT)  // if hit bottom screen edge
    {
        spriteData.y = GAME_HEIGHT-banditNS::HEIGHT;  // position at bottom screen edge
        velocity.y = -velocity.y;                   // reverse Y direction
    } else if (spriteData.y < 0)                    // else if hit top screen edge
    {
        spriteData.y = 0;                           // position at top screen edge
        velocity.y = -velocity.y;                   // reverse Y direction
    }
   
}

//=============================================================================
// damage
//=============================================================================
//void Bandit::damage(WEAPON weapon)
//{
//    shieldOn = true;
//}

