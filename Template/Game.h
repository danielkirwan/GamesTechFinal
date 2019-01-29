#pragma once

#define _USE_MATH_DEFINES								// Will allow certain constants (like M_PI) to be availabe from <math.h>

#include <windows.h>									// Header File For the Windows Library
#include <stdio.h>										// Header File For the Standard Input/Output Functions
#include <stdlib.h>										// Header File For the Standard Library
#include <math.h>										// Header File For the Math header file
#include ".\include\glew.h"								// Header File For the GLEW Library
#include ".\include\GL.H"								// Header File For the OpenGL32 Library
#include ".\include\glu.h"								// Header File For the GLu32 Library
#include <vector>

// Includes for game objects
#include "Camera.h"
#include "Gamewindow.h"
#include "HighResolutionTimer.h"
#include "Terrain.h"
#include "SkyBox.h"
#include "OpenAssetImporterMesh.h"
#include "BouncingBall.h"
#include "Audio.h"
#include "Text.h"
#include "Lighting.h"
#include "Material.h"
#include "Md2Animation.h"
#include "SpecialFX.h"
#include "Tetrahedron.h"
#include "Cube.h"
#include "Player.h"
#include "Score.h"
#include "Bobbafett.h"
#include "Wall.h"
#include "Jeep.h"
#include "Stonewall.h"
#include "CFreddie.h"
#include "Fireball.h"
#include "CrossFade.h"
#include "LightningBolt.h"
#include "Dragon.h"
#include "Xenoid.h"
#include "Medkit.h"
#include "SpriteExplosion.h"
#include "Health.h"
#include "Hands.h"

class Game {
public:

private:
	void Initialise();		// Initialises the games (load assets, etc.)
	void Update();			// Update the simulation at each time step
	void Render();			// Render the scene
	void GameLoop();		// The game loop

	// Game objects
	Camera m_camera;								// The camera
	
	CHighResolutionTimer m_highResolutionTimer;		// A timer for measuring the time between frames
	CTerrain m_terrain;								// The terrain (planar)
	CSkybox m_skybox;								// A skybox surrounding the scene
	CAudio m_audio;									// Audio using FMOD
	CAudio m_audioWall;								//Collison for walls
	CAudio m_backgroundaudio;						//Background audio
	CText m_text;									// Text for the head's up display
	CLighting m_lighting;							// Lighting 
	CLighting m_pointLight;
	CCrossFade m_crossFade;							//Crossfade effect
	CSpecialFX m_fx;								//Creat the fog
	CTetrahedron m_tetrahedron;						//Tetrahedron variable
	CCube m_cube;									//cube member variable
	CCube m_wall1;									//Cube as a wall
	CJeep m_jeep1;									//Creat a jeep
	CPlayer m_player;								//player variable
	CScore m_score;									//access to score
	CHealth m_healthNew;
	CXenoid xenoid;									//Create a xenoid enemy
	CXenoid xenoid2;								//Create a xenoid enemy
	int m_health;									//Health
	CFireball m_fireball;							//Fireball
	std::vector<CLightningBolt> m_lightningBolts;	//Lightning bolt
	CDragon m_dragon1;								//Create Dragon
	int m_dragonHealth;								//Dragon health
	CBobbafett m_bobbafett;							//Create bobbafett
	CBobbafett m_bobbafett2;						//Create bobbafett
	bool m_introScreen;								// A boolean flag indicating if the intro screen is on
	double m_dt;									// A variable to measure the amount of time elasped between frames
	int m_animation;								// Current animation of MD2 model
	int m_numBolts;									//number of bolts for lightning
	CVector3f m_whiteLightPos;						//Point light position
	int m_fireballHeath;							//Fireball health
	CMedkit m_medkit;								//Create medkit
	CHands m_hands;
	std::vector <CCube> cubes;						//Vector of cube objects
	int m_cubes = 20;								//Number to easily change the number of cubes in the vector array
	CWall backWall;									//Game world wall
	CWall frontWall;								//Game world wall
	CWall leftSide;									//Game world wall
	CWall rightSide;								//Game world wall
	CSpriteExplosion m_spriteExplosion;				//Sprite explosion

	CStonewall m_stonewall;							//Castle wall mesh
	CFreddie m_freddie;								//Freddie mesh

	std::vector<CWall> section1xwall;				//Section 1 x vector of walls
	std::vector<CVector3f> section1xwallvectors;	//Section 1 x vector of points

	std::vector<CWall> section1ywall;				//Section 1 y vector of walls
	std::vector<CVector3f> section1ywallvectors;	//Section 1 y vector of points

	std::vector<CWall> section2xwall;				//Section 2 x vector of walls
	std::vector<CVector3f> section2xwallvectors;	//Section 2 x vector of points

	std::vector<CWall> section2ywall;				//Section 2 y vector of walls
	std::vector<CVector3f> section2ywallvectors;	//Section 2 y vector of walls

	std::vector<CWall> section3xwall;				//Section 3 x vector of walls
	std::vector<CVector3f> section3xwallvectors;	//Section 3 x vector of points

	std::vector<CWall> section3ywall;				//Section 3 y vector of walls
	std::vector<CVector3f> section3ywallvectors;	//Section 3 y vector of points

	std::vector<CWall> section4xwall;				//Section 4 x vector of walls
	std::vector<CVector3f> section4xwallvectors;	//Section 4 x vector of walls

	std::vector<CWall> section4ywall;				//Section 4 y vector of walls
	std::vector<CVector3f> section4ywallvectors;	//Section 4 y vector of points

public:
	~Game();
	static Game& GetInstance();
	WPARAM Execute();
	void SetHinstance(HINSTANCE hinstance);
	LRESULT ProcessEvents(HWND window,UINT message, WPARAM w_param, LPARAM l_param);
	

private:
	Game::Game();
	Game::Game(const Game&);
	void Game::operator=(const Game&);

	GameWindow m_GameWindow;
	HINSTANCE m_hinstance;


};