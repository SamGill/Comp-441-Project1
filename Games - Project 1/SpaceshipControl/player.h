// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.h v1.0

#ifndef _PLAYER_H                 // Prevent multiple definitions if this 
#define _PLAYER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace playerNS
{
    const int WIDTH = 128;                   // image width
    const int HEIGHT = 128;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT - HEIGHT;
    const float SPEED = 60;                
    
	//Not sure if this is needed
	const float MASS = 300.0f;              // mass
    //
	
	const int   TEXTURE_COLS = 8;           // texture has 8 columns


    //const int   SHIP1_START_FRAME = 0;      // ship1 starts at frame 0
    //const int   SHIP1_END_FRAME = 3;        // ship1 animation frames 0,1,2,3
    //const int   SHIP2_START_FRAME = 8;      // ship2 starts at frame 8
    //const int   SHIP2_END_FRAME = 11;       // ship2 animation frames 8,9,10,11
    //const float SHIP_ANIMATION_DELAY = 0.2f;    // time between frames
    //const int   SHIELD_START_FRAME = 24;    // shield start frame
    //const int   SHIELD_END_FRAME = 27;      // shield end frame
    //const float SHIELD_ANIMATION_DELAY = 0.1f; // time between frames
}

// inherits from Entity class
class Player : public Entity
{
public:
    // constructor
    Player();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);

    void damage(WEAPON);
};
#endif

