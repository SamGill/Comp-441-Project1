// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 5 Desperado.h v1.0

#ifndef _DESPERADO_H             // Prevent multiple definitions if this 
#define _DESPERADO_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "bandit.h"
#include "bullet.h"
#include "player.h"
#include "textDX.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class Desperado : public Game
{
private:
	
	//Actual Game textures
	TextureManager cactusTexture;    // cactus texture
	TextureManager banditTexture;
	TextureManager backgroundTexture;
	TextureManager bulletTexture;
	TextureManager goldTexture;
	TextureManager heartTexture;
	TextureManager playerTexture;

	Image cactus;					// cactus image
	Bandit bandit;
	Bandit manyBandits[5];
	Image background;
	Bullet playerBullet;
	Player player;

	Image hearts[5];
	Image golds[3];

	TextDX *scoreFont; //Text used to display score
	TextDX *wave; //Text used to display current wave
	TextDX *victory; //Text displayed when player successfully completes game
	TextDX *gameOver; //Text displayed when player dies
	
	// game items
	TextureManager nebulaTexture;   // nebula texture
	TextureManager planetTexture;   // planet texture
	TextureManager shipTexture;     // ship texture
	Image   planet;                 // planet image
	Image   nebula;                 // nebula image
	Image   ship;                   // ship image

public:
	// Constructor
	Desperado();

	// Destructor
	virtual ~Desperado();

	// Initialize the game
	void initialize(HWND hwnd);
	void update();      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();
};

#endif
