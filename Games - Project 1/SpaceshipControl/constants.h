// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 5 constants.h v1.0
#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// graphic images
const char NEBULA_IMAGE[] = "pictures\\orion.jpg";  // photo source NASA/courtesy of nasaimages.org 
const char PLANET_IMAGE[] = "pictures\\planet.png"; // picture of planet
const char SHIP_IMAGE[]   = "pictures\\ship.png";   // spaceship
const char CACTUS_IMAGE[] = "pictures\\cactus.png";

const char BANDIT_IMAGE[]     = "pictures\\bandit.png";
const char BACKGROUND_IMAGE[] = "pictures\\background.png";
const char BULLET_IMAGE[]	  = "pictures\\bullet.png";
const char GOLD_IMAGE[]		  = "pictures\\gold.png";
const char HEART_IMAGE[]	  = "pictures\\heart.png";
const char PLAYER_IMAGE[]	  = "pictures\\player.png";


// window
const char CLASS_NAME[] = "Desperado";
const char GAME_TITLE[] = "Desperado";
const bool FULLSCREEN   = false;              // windowed or fullscreen
const UINT GAME_WIDTH   = 1024;               // width of game in pixels
const UINT GAME_HEIGHT  = 1024;               // height of game in pixels

#pragma region Ship_Constants

const int  SHIP_START_FRAME = 0;            // starting frame of ship animation
const int  SHIP_END_FRAME = 3;              // last frame of ship animation
const float SHIP_ANIMATION_DELAY = 0.2f;    // time between frames of ship animation
const int  SHIP_COLS = 2;                   // ship texture has 2 columns
const int  SHIP_WIDTH = 32;                 // width of ship image
const int  SHIP_HEIGHT = 32;                // height of ship image
const float SHIP_SCALE = 1.5f;              // starting ship scale

#pragma endregion


const float ROTATION_RATE = 180.0f;         // degrees per second
const float SCALE_RATE = 0.2f;              // % change per second

const float PLAYER_SPEED = 250.0f;            // pixels per second
const float	BULLET_SPEED = 750.0f;
const int   HEART_NUMBER = 5;
const int   GOLD_NUMBER  = 3;
const int	BANDIT_SPEED = 60;
const int   MAX_BANDITS  = 5;

const int waveDelay = 200;

const int PIXEL_SPACE = 10;



// game
const double PI = 3.14159265;
const float FRAME_RATE  = 200.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY      = VK_MENU;         // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;       // Enter key


enum WEAPON {BULLET, BANDIT};

// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[]  = "audio\\Win\\WavesExample1.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\SoundsExample1.xsb";

// audio cues
const char BEEP1[] = "beep1";
const char BEEP2[] = "beep2";
const char BEEP3[] = "beep3";
const char BEEP4[] = "beep4";
const char HIT[]   = "hit";

#endif