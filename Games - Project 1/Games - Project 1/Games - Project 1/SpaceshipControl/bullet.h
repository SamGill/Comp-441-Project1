// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.h v1.0

#ifndef _BULLET_H                 // Prevent multiple definitions if this 
#define _BULLET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace bulletNS
{
    const int WIDTH = 16;                   // image width
    const int HEIGHT = 16;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = 0;
    const float SPEED = 750.0f;                
    
	const float BANDIT_SPEED = 300.0f;
	//Not sure if this is needed
	const float MASS = 300.0f;              // mass
    //
	
	const int   TEXTURE_COLS = 8;           // texture has 8 columns
}

// inherits from Entity class
class Bullet : public Entity
{
public:
    // constructor
    Bullet();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);
	void banditUpdate(float frameTime);
    //void damage(WEAPON);
};
#endif

