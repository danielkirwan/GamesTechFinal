/* 
OpenGL Template for IN3026
City University London, School of Informatics
Source code drawn from a number of sources and examples, including contributions from
 - Ben Humphrey (gametutorials.com), Christy Quinn, Sam Kellett, and others

 For educational use by Deparment of Computer Science, City University London UK.

 This template contains a skybox, simple terrain, camera, lighting, mesh loader, sipmle physics, texturing, audio

 Potential ways to modify the code:  Add new geometry types, change the terrain, load new meshes, set up lighting, 
 add in additional music / sound FX, modify camera control, put in a startup screen, collision detection, etc.
 
 Template version 4.0a 13/09/2017
 Dr Greg Slabaugh (gregory.slabaugh.1@city.ac.uk) 
*/


#include "Game.h"
#include "Cube.h"


// Constructor.  
Game::Game()  
{
	m_introScreen = true;				//Introscreen set to true
	m_dt = 0.0f;						//time					
	m_animation = 0;					//animation
	m_health = 100;						//Player health
	m_numBolts = 3;						//number of lightning bolts
	m_fireballHeath = 1;				//Fireball health
	m_dragonHealth = 2;					//Dragon health as there is only one in the game
}

// Destructor.  Technically we could delete all resources, but when the game ends the OS will free memory for us.
Game::~Game() 
{ 
}

// Initialise the game by loading assets and setting up the scene.  Note, it's best to make OpenGL calls here since we know the rendering context is available.
void Game::Initialise() 
{
	// Initialise the camera (position, view point, upvector, and speed)
	//m_camera.Set(CVector3f(0, 2, 10), CVector3f(0, 0, 1), CVector3f(0, 1, 0), 15.0f);
	m_camera.Set(CVector3f(0, 2, -25), CVector3f(0, 0, -1), CVector3f(0, 1, 0), 15.0f);

	// Create the terrain and skybox
	m_terrain.Initialise();
	m_skybox.Create("", 0.0f);

	m_whiteLightPos = CVector3f(0, 5, 0);
	//m_hands.Initialise("Resources\\meshes\\hands\\Half_Life_2_Rig.blend", CVector3f(0,0,0));
	//m_hands.Initialise(CVector3f(0,0,0));

	//creates the rock with texture
	m_tetrahedron.Initialise();
	// Create a class for rendering text
	m_text.Create(m_GameWindow.GetHdc(), "Arial", 18);

	glClearColor(1, 1, 1, 1);

	// Load some meshes
	m_jeep1.Initialise(CVector3f(-75.0f,0.0f,75.0f));
	m_dragon1.Initialise(CVector3f(75,2,75));
	m_stonewall.Initialise(CVector3f(0.0f,0.0f,75.0f));
	m_freddie.Initialise(CVector3f(-10,0,10));
	m_bobbafett.Initialise(CVector3f(-30,0,-15));
	m_bobbafett2.Initialise(CVector3f(-30,0,15));
	backWall.Initialise(CVector3f(0.0f,0.0f,-125.0f));
	frontWall.Initialise(CVector3f(0.0f,0.0f,125.0f));
	leftSide.Initialise(CVector3f(125.0f,0.0f,0.0f));
	rightSide.Initialise(CVector3f(-125.0f, 0.0f, 0.0f));
	m_fireball.Initialise("Resources\\meshes\\fireball.obj");
	m_medkit.Initialise(CVector3f(-10.0f, 1.5f, -10.0f));
	m_spriteExplosion.Initialise("Resources\\Textures\\Explosion.tga", 4, 5, 16);

	// Initialise audio and play background music
	m_audio.Initialise();
	m_audioWall.Initialise();												// Royalty free sound from freesound.org
	m_audioWall.LoadEventSound("Resources\\Audio\\wall2.wav");
	//m_backgroundaudio.Initialise();
	//m_backgroundaudio.LoadMusicStream("Resources\\Audio\background.mp3");
	//m_backgroundaudio.PlayMusicStream();
	m_audio.LoadMusicStream("Resources\\Audio\background.mp3");					//Royalty fee sound from freesound.org
	//m_audio.LoadMusicStream("Resources\\Audio\\DST-impuretechnology.mp3");	// Royalty free music from http://www.nosoapradio.us/
	m_audio.PlayMusicStream();

	// Load an animated character -- free to use from http://www.gamers.org/pub/idgames2/quake2/graphics/md2/ 

	//Initialise the xenoid enemy
	xenoid.Initialise(CVector3f(-20,0,-30));
	xenoid2.Initialise(CVector3f(20,0,-30));
	m_healthNew.Initialise(150);


	//section 1 x walls vectors and push into vector
	CVector3f xwall1 = CVector3f(-117.0f, 0.0f, -50.0f);
	CVector3f xwall2 = CVector3f(-103.0f, 0.0f, -50.0f);
	CVector3f xwall3 = CVector3f(-89.0f, 0.0f, -50.0f);
	CVector3f xwall4 = CVector3f(-75.0f, 0.0f, -50.0f);
	CVector3f xwall5 = CVector3f(-61.0f, 0.0f, -50.0f);
	section1xwallvectors.push_back(xwall1);
	section1xwallvectors.push_back(xwall2);
	section1xwallvectors.push_back(xwall3);
	section1xwallvectors.push_back(xwall4);
	section1xwallvectors.push_back(xwall5);

	for (int i = 0; i < section1xwallvectors.size();i++)
	{
		CWall section1xwalls;
		section1xwalls.Initialise(section1xwallvectors[i]);
		section1xwall.push_back(section1xwalls);
	}

	//section 1 y walls vectors and push into vector
	CVector3f ywall1 = CVector3f(-50.0f, 0.0f, -117.0f);
	CVector3f ywall2 = CVector3f(-50.0f, 0.0f, -103.0f);
	CVector3f ywall3 = CVector3f(-50.0f, 0.0f, -89.0f);
	CVector3f ywall4 = CVector3f(-50.0f, 0.0f, -75.0f);
	CVector3f ywall5 = CVector3f(-50.0f, 0.0f, -61.0f);
	section1ywallvectors.push_back(ywall1);
	section1ywallvectors.push_back(ywall2);
	section1ywallvectors.push_back(ywall3);
	section1ywallvectors.push_back(ywall4);
	section1ywallvectors.push_back(ywall5);

	for (int i = 0; i < section1ywallvectors.size(); i++)
	{
		CWall section1ywalls;
		section1ywalls.Initialise(section1ywallvectors[i]);
		section1ywall.push_back(section1ywalls);
	}

	//section 2 x walls vectors and push into vector
	CVector3f s2xwall1 = CVector3f(117.0f, 0.0f, -50.0f);
	CVector3f s2xwall2 = CVector3f(103.0f, 0.0f, -50.0f);
	CVector3f s2xwall3 = CVector3f(89.0f, 0.0f, -50.0f);
	CVector3f s2xwall4 = CVector3f(75.0f, 0.0f, -50.0f);
	CVector3f s2xwall5 = CVector3f(61.0f, 0.0f, -50.0f);
	section2xwallvectors.push_back(s2xwall1);
	section2xwallvectors.push_back(s2xwall2);
	section2xwallvectors.push_back(s2xwall3);
	section2xwallvectors.push_back(s2xwall4);
	section2xwallvectors.push_back(s2xwall5);
	for (int i = 0; i < section2xwallvectors.size(); i++)
	{
		CWall section2xwalls;
		section2xwalls.Initialise(section2xwallvectors[i]);
		section2xwall.push_back(section2xwalls);
	}

	//section2 y walls vectors and push into vector
	CVector3f s2ywall1 = CVector3f(50.0f, 0.0f, -117.0f);
	CVector3f s2ywall2 = CVector3f(50.0f, 0.0f, -103.0f);
	CVector3f s2ywall3 = CVector3f(50.0f, 0.0f, -89.0f);
	CVector3f s2ywall4 = CVector3f(50.0f, 0.0f, -75.0f);
	CVector3f s2ywall5 = CVector3f(50.0f, 0.0f, -61.0f);
	section2ywallvectors.push_back(s2ywall1);
	section2ywallvectors.push_back(s2ywall2);
	section2ywallvectors.push_back(s2ywall3);
	section2ywallvectors.push_back(s2ywall4);
	section2ywallvectors.push_back(s2ywall5);
	for (int i = 0; i < section2ywallvectors.size(); i++)
	{
		CWall section2ywalls;
		section2ywalls.Initialise(section2ywallvectors[i]);
		section2ywall.push_back(section2ywalls);
	}

	//section 3 x walls vectors and push into vector
	CVector3f s3xwall1 = CVector3f(117.0f, 0.0f, 50.0f);
	CVector3f s3xwall2 = CVector3f(103.0f, 0.0f, 50.0f);
	CVector3f s3xwall3 = CVector3f(89.0f, 0.0f, 50.0f);
	CVector3f s3xwall4 = CVector3f(75.0f, 0.0f, 50.0f);
	CVector3f s3xwall5 = CVector3f(61.0f, 0.0f, 50.0f);
	section3xwallvectors.push_back(s3xwall1);
	section3xwallvectors.push_back(s3xwall2);
	section3xwallvectors.push_back(s3xwall3);
	section3xwallvectors.push_back(s3xwall4);
	section3xwallvectors.push_back(s3xwall5);

	for (int i = 0; i < section3xwallvectors.size(); i++)
	{
		CWall section3xwalls;
		section3xwalls.Initialise(section3xwallvectors[i]);
		section3xwall.push_back(section3xwalls);
	}

	//section3 y walls vectors and push into vector
	CVector3f s3ywall1 = CVector3f(50.0f, 0.0f, 117.0f);
	CVector3f s3ywall2 = CVector3f(50.0f, 0.0f, 103.0f);
	CVector3f s3ywall3 = CVector3f(50.0f, 0.0f, 89.0f);
	CVector3f s3ywall4 = CVector3f(50.0f, 0.0f, 75.0f);
	CVector3f s3ywall5 = CVector3f(50.0f, 0.0f, 61.0f);
	section3ywallvectors.push_back(s3ywall1);
	section3ywallvectors.push_back(s3ywall2);
	section3ywallvectors.push_back(s3ywall3);
	section3ywallvectors.push_back(s3ywall4);
	section3ywallvectors.push_back(s3ywall5);

	for (int i = 0; i < section3ywallvectors.size(); i++)
	{
		CWall section3ywalls;
		section3ywalls.Initialise(section3ywallvectors[i]);
		section3ywall.push_back(section3ywalls);
	}

	//section 4 x walls vectors and push into vector
	CVector3f s4xwall1 = CVector3f(-117.0f, 0.0f, 50.0f);
	CVector3f s4xwall2 = CVector3f(-103.0f, 0.0f, 50.0f);
	CVector3f s4xwall3 = CVector3f(-89.0f, 0.0f, 50.0f);
	CVector3f s4xwall4 = CVector3f(-75.0f, 0.0f, 50.0f);
	CVector3f s4xwall5 = CVector3f(-61.0f, 0.0f, 50.0f);
	section4xwallvectors.push_back(s4xwall1);
	section4xwallvectors.push_back(s4xwall2);
	section4xwallvectors.push_back(s4xwall3);
	section4xwallvectors.push_back(s4xwall4);
	section4xwallvectors.push_back(s4xwall5);
	for (int i = 0; i < section4xwallvectors.size(); i++)
	{
		CWall section4xwalls;
		section4xwalls.Initialise(section4xwallvectors[i]);
		section4xwall.push_back(section4xwalls);
	}

	//section 4 y walls vectors and push into vector
	CVector3f s4ywall1 = CVector3f(-50.0f, 0.0f, 117.0f);
	CVector3f s4ywall2 = CVector3f(-50.0f, 0.0f, 103.0f);
	CVector3f s4ywall3 = CVector3f(-50.0f, 0.0f, 89.0f);
	CVector3f s4ywall4 = CVector3f(-50.0f, 0.0f, 75.0f);
	CVector3f s4ywall5 = CVector3f(-50.0f, 0.0f, 61.0f);
	section4ywallvectors.push_back(s4ywall1);
	section4ywallvectors.push_back(s4ywall2);
	section4ywallvectors.push_back(s4ywall3);
	section4ywallvectors.push_back(s4ywall4);
	section4ywallvectors.push_back(s4ywall5);

	for (int i = 0; i < section4ywallvectors.size(); i++)
	{
		CWall section4ywalls;
		section4ywalls.Initialise(section4ywallvectors[i]);
		section4ywall.push_back(section4ywalls);
	}

	//For loop for initialising the vector with cubes.
	for (int i =0; i < m_cubes;i++ )
	{
		//From the help of Alejandro Davila from my question om Moodle
		CCube myCube;
		myCube.Initialise(CVector3f(50, 2, 35));
		cubes.push_back(myCube);
	}

	//initialise the score
	m_score.Initialise(0);

	//Initialise the lightning bolts
	for (int i = 0; i < m_numBolts; i++) {
		CLightningBolt lb;
		CVector3f direction = CVector3f(-m_camera.GetPosition().x, m_camera.GetPosition().y, -m_camera.GetPosition().z);
		lb.ComputePath(m_dragon1.GetPosition(), direction);
		m_lightningBolts.push_back(lb);
	}

}

// Update game objects using a timer
void Game::Update()
{
	//Resets the player position when a collision occurs
	CVector3f Cam_pos = m_camera.GetPosition();
	float speed = 5.0f;
	if (GetFocus() == m_GameWindow.GetHwnd())

		//normal camera movement
		m_camera.Update(m_dt);

	// Often it will be useful to perform collision detection and response in Update()
	
	// Periodically update audio being played back by FMOD
	m_audio.Update();
	//Update background audio
	m_backgroundaudio.Update();

	//Update the special effects
	m_crossFade.Update(m_dt);
	m_spriteExplosion.Update(m_dt);

	//For loop for updating the cube objects
	for (int i = 0; i < m_cubes; i++)
	{
		//Added in new getPosition for the cube so the update function knows which cube is being deactivated 
		//when in contact with the player
		cubes[i].Update(m_camera.GetPosition(), m_dt, &m_score, cubes[i].GetPosition());

	}

	//Collision detection for player and inside walls
	for (int i = 0; i < section1xwall.size(); i++)
	{
		if (section1xwall[i].GetBBox().Collision(m_camera.GetBBox()))
		{
			m_camera.SetPosition(Cam_pos);
			m_crossFade.Activate();
			m_health--;
			m_audioWall.PlayEventSound();
		}
	}
	//Collision detection for player and inside walls
	for (int i = 0; i < section1ywall.size(); i++)
	{
		if (section1ywall[i].GetBBox().Collision(m_camera.GetBBox()))
		{
			m_camera.SetPosition(Cam_pos);
			m_crossFade.Activate();
			m_health--;
			m_audioWall.PlayEventSound();
		}
	}
	//Collision detection for player and inside walls
	for (int i = 0; i < section2xwall.size(); i++)
	{
		if (section2xwall[i].GetBBox().Collision(m_camera.GetBBox()))
		{
			m_camera.SetPosition(Cam_pos);
			m_crossFade.Activate();
			m_health--;
			m_audioWall.PlayEventSound();
		}

	}
	//Collision detection for player and inside walls
	for (int i = 0; i < section2ywall.size(); i++)
	{
		if (section2ywall[i].GetBBox().Collision(m_camera.GetBBox()))
		{
			m_camera.SetPosition(Cam_pos);
			m_crossFade.Activate();
			m_health--;
			m_audioWall.PlayEventSound();
		}

	}
	//Collision detection for player and inside walls
	for (int i = 0; i < section3xwall.size(); i++)
	{
		if (section3xwall[i].GetBBox().Collision(m_camera.GetBBox()))
		{
			m_camera.SetPosition(Cam_pos);
			m_crossFade.Activate();
			m_health--;
			m_audioWall.PlayEventSound();
		}

	}
	//Collision detection for player and inside walls
	for (int i = 0; i < section3ywall.size(); i++)
	{
		if (section3ywall[i].GetBBox().Collision(m_camera.GetBBox()))
		{
			m_camera.SetPosition(Cam_pos);
			m_crossFade.Activate();
			m_health--;
			m_audioWall.PlayEventSound();
		}

	}
	//Collision detection for player and inside walls
	for (int i = 0; i < section4xwall.size(); i++)
	{
		if (section4xwall[i].GetBBox().Collision(m_camera.GetBBox()))
		{
			m_camera.SetPosition(Cam_pos);
			m_crossFade.Activate();
			m_health--;
			m_audioWall.PlayEventSound();
		}

	}
	//Collision detection for player and inside walls
	for (int i = 0; i < section4ywall.size(); i++)
	{
		if (section4ywall[i].GetBBox().Collision(m_camera.GetBBox()))
		{
			m_camera.SetPosition(Cam_pos);
			m_crossFade.Activate();
			m_health--;
			m_audioWall.PlayEventSound();
		}

	}
	//Updates the lightning bolts so that it stops after certain timeframe
	for (int i = 0; i < m_numBolts; i++) {
		CVector3f direction = CVector3f(-m_camera.GetPosition().x, m_camera.GetPosition().y, -m_camera.GetPosition().z);
		m_lightningBolts[i].ComputePath(m_dragon1.GetPosition() + CVector3f(0, 3, 0), direction);
		m_lightningBolts[i].Update(m_dt);
	}

	//Distance algorithm for Dragon to fire lightning bolts
	float scalarResult;
	CVector3f dragon_pos = m_dragon1.GetPosition();
	CVector3f cam_pos = m_camera.GetPosition();
	CVector3f dis = cam_pos - dragon_pos;
	scalarResult = dis.Length();
	if (scalarResult < 20.0f)
	{
		for (int i = 0; i < m_numBolts; i++) {
			m_lightningBolts[i].Activate();
			CVector3f direction = CVector3f(-m_camera.GetPosition().x, m_camera.GetPosition().y, -m_camera.GetPosition().z);
			m_lightningBolts[i].ComputePath(m_dragon1.GetPosition()+ CVector3f(0,3,0), direction);
		}
	}

	//Determines whether the player has collided with the walls
	if (backWall.GetBBox().Collision(m_camera.GetBBox()) ||
		frontWall.GetBBox().Collision(m_camera.GetBBox()) ||
		leftSide.GetBBox().Collision(m_camera.GetBBox()) ||
		rightSide.GetBBox().Collision(m_camera.GetBBox())||
		m_jeep1.GetBBox().Collision(m_camera.GetBBox()) ||
		m_stonewall.GetBBox().Collision(m_camera.GetBBox()) ||
		m_freddie.GetBBox().Collision(m_camera.GetBBox()) ||
		xenoid.GetBBox().Collision(m_camera.GetBBox()) ||
		xenoid2.GetBBox().Collision(m_camera.GetBBox()) ||
		m_bobbafett.GetBBox().Collision(m_camera.GetBBox()) ||
		m_bobbafett2.GetBBox().Collision(m_camera.GetBBox()) ||
		m_dragon1.GetBBox().Collision(m_camera.GetBBox()))
	{
		m_camera.SetPosition(Cam_pos);
		m_crossFade.Activate();
		m_health--;
		m_audioWall.PlayEventSound();
	}

	if (m_fireballHeath > 0)
	{
		m_fireball.Update(m_dt);
	}

	//Only run the xenoid update if the xenoid health is more than 0
	if (xenoid.health > 0)
	{
		xenoid.Update(m_dt, m_camera.GetPosition());
	}

	//Determines whether the xenoid has been hit and decide if it should be destroyed
	if (m_fireball.GetBBox().Collision(xenoid.GetBBox()))
	{
		xenoid.health -= m_fireball.damage;
		m_spriteExplosion.Activate();
		if (xenoid.health <= 0)
		{
			xenoid.~CXenoid();
			m_score.m_score = m_score.m_score + 20;
		}

	}

	//Only run the xenoid update if the xenoid health is more than 0
	if (xenoid2.health > 0)
	{
		xenoid2.Update(m_dt, m_camera.GetPosition());
	}

	//Determines whether the xenoid has been hit and decide if it should be destroyed
	if (m_fireball.GetBBox().Collision(xenoid2.GetBBox()))
	{
		xenoid2.health -= m_fireball.damage;
		m_spriteExplosion.Activate();
		if (xenoid2.health <= 0)
		{
			xenoid2.~CXenoid();
			m_score.m_score = m_score.m_score + 20;
		}

	}

	//Only run the bobbafett update if the bobbafett health is more than 0
	if (m_bobbafett.health > 0)
	{
		m_bobbafett.Update(m_dt, m_camera.GetPosition());
	}
	//Determines whether bobbafetrt has been hit and decide if it should be destroyed
	if (m_fireball.GetBBox().Collision(m_bobbafett.GetBBox()))
	{
		m_bobbafett.health -= m_fireball.damage;
		m_spriteExplosion.Activate();
		if (m_bobbafett.health <= 0)
		{
			m_bobbafett.~CBobbafett();
			m_score.m_score = m_score.m_score + 20;
		}
	}

	//Only run the bobbafett update if the bobbafett health is more than 0
	if (m_bobbafett2.health > 0)
	{
		m_bobbafett2.Update(m_dt, m_camera.GetPosition());
	}
	//Determines whether bobbafetrt has been hit and decide if it should be destroyed
	if (m_fireball.GetBBox().Collision(m_bobbafett2.GetBBox()))
	{
		m_bobbafett2.health -= m_fireball.damage;
		m_spriteExplosion.Activate();
		if (m_bobbafett2.health <= 0)
		{
			m_bobbafett2.~CBobbafett();
			m_score.m_score = m_score.m_score + 20;
		}
	}

	//Determines whether the fireball has hit the dragon and decide if it should be destroyed
	if (m_fireball.GetBBox().Collision(m_dragon1.GetBBox()))
	{
		m_dragonHealth -= m_fireball.damage;
		m_spriteExplosion.Render(CVector3f(0, 10, 0), m_camera.GetViewPoint() - m_camera.GetPosition(), m_camera.GetUpVector(), 10, 10);
		if (m_dragonHealth <= 0)
		{
			m_dragon1.~CDragon();
			m_score.m_score = m_score.m_score + 30;
		}
	}

	//Update the medkit with the camera position to determine whether it has been picked up
	//This doesn't work
	m_medkit.Update(m_camera.GetPosition(), &m_healthNew, m_dt, m_medkit.GetPosition());

	//This doesn't work
	/*
	if (m_medkit.GetBBox().Collision(m_camera.GetBBox()))
	{
		m_medkit.m_isActive = false;
		m_score.m_score = m_score.m_score + m_medkit.healthIncrease;
	}*/

	if (m_health <= 0)
	{
		PostQuitMessage(0);
	}
		

	m_GameWindow.UpdateFrameRate(m_dt);

	//m_score.Update(m_score.score);
}

// Render the scene
void Game::Render() 
{
	// GLuint errCode = glGetError(); // Can check for OpenGL errors with this -- should be zero if no error

	// Clear the buffers and load the identity matrix into the modelview matrix
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Calling look will put the viewing matrix onto the modelview matrix stack
	m_camera.Look();

	// Get the camera position and view vector
	CVector3f vPos	= m_camera.GetPosition();
	CVector3f vView = m_camera.GetViewPoint();


	if (m_introScreen == true) {	//If we are on an introscreen, we can render it here, else...
		//render some text on Intro screen
		glDisable(GL_LIGHTING);
		m_text.Render("Collector", (m_GameWindow.SCREEN_WIDTH /2), (m_GameWindow.SCREEN_HEIGHT /2 + 200),0, 0, 0);
		m_text.Render("Controls", (m_GameWindow.SCREEN_WIDTH / 2), ((m_GameWindow.SCREEN_HEIGHT / 2)+ 150),0, 0, 0);
		m_text.Render("Strafe Left", (m_GameWindow.SCREEN_WIDTH / 2 - 100), ((m_GameWindow.SCREEN_HEIGHT / 2)+100 ), 0, 0, 0);
		m_text.Render("A", (m_GameWindow.SCREEN_WIDTH / 2), ((m_GameWindow.SCREEN_HEIGHT / 2)+100 ), 1, 0, 0);
		m_text.Render("Strafe right", (m_GameWindow.SCREEN_WIDTH / 2 - 100), ((m_GameWindow.SCREEN_HEIGHT / 2) +50), 0, 0, 0);
		m_text.Render("D", (m_GameWindow.SCREEN_WIDTH / 2), ((m_GameWindow.SCREEN_HEIGHT / 2)+50), 1, 0, 0);
		m_text.Render("Forwards", (m_GameWindow.SCREEN_WIDTH / 2 - 100), ((m_GameWindow.SCREEN_HEIGHT / 2) + 0), 0, 0, 0);
		m_text.Render("W", (m_GameWindow.SCREEN_WIDTH / 2), ((m_GameWindow.SCREEN_HEIGHT / 2) + 0), 1, 0, 0);
		m_text.Render("Backwards", (m_GameWindow.SCREEN_WIDTH / 2 - 100), ((m_GameWindow.SCREEN_HEIGHT / 2) - 50), 0, 0, 0);
		m_text.Render("S", (m_GameWindow.SCREEN_WIDTH / 2), ((m_GameWindow.SCREEN_HEIGHT / 2) - 50), 1, 0, 0);
		m_text.Render("Fire", (m_GameWindow.SCREEN_WIDTH / 2 - 100), ((m_GameWindow.SCREEN_HEIGHT / 2) - 100), 0, 0, 0);
		m_text.Render("4", (m_GameWindow.SCREEN_WIDTH / 2), ((m_GameWindow.SCREEN_HEIGHT / 2) - 100), 1, 0, 0);

		m_text.Render("Collect all the cubes", (m_GameWindow.SCREEN_WIDTH / 2 ) - 100, ((m_GameWindow.SCREEN_HEIGHT / 2) - 150), 0, 1, 0);

		m_text.Render("Press M to start", (m_GameWindow.SCREEN_WIDTH / 2) - 100, ((m_GameWindow.SCREEN_HEIGHT / 2) - 200), 0, 0, 0);
		glEnable(GL_LIGHTING);


	} else {
		// Render skybox with no lighting
		glDisable(GL_LIGHTING);
		m_skybox.Render(vPos.x, vPos.y, vPos.z, 1000, 500, 1000);  // Render the skybox with lighting off
		//m_text.Render(" Score here", 10, 540, 1, 0.5, 0);  // Draw some text -- useful for debugging and head's up displays
		glEnable(GL_LIGHTING);

		glDisable(GL_LIGHTING);
		char scoreText[128];
		sprintf_s(scoreText, "Score = %d\n", m_score.m_score);
		m_text.Render(scoreText, 10, 540, 1, 0.5, 0);
		char healthText[128];
		//sprintf_s(healthText, "Health = %d\n", m_health);
		sprintf_s(healthText, "Health = %d\n", m_healthNew.m_health);
		m_text.Render(healthText, 10, 520,1,0.5,0);
		glEnable(GL_LIGHTING);


		// Set materials and lighting for the scene
		m_lighting.SetDefaultLighting();
		//m_lighting.SetLights(m_whiteLightPos);
		//m_pointLight.SetLights(m_whiteLightPos);

		// Render the terrain
		m_terrain.Render();

		//Render the jeep
		m_jeep1.Render();
		//Render Dragon
		m_dragon1.Render();
		//Render xenoid
		xenoid.Render();
		xenoid2.Render();
		//Render Medkit
		m_medkit.Render();

		//Render the tetrahedron
		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glTranslatef(-75,0,-75);
			m_tetrahedron.Render(1, 1, 1, 1);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glPopMatrix();

		//render fireball
		m_fireball.Render();

		//Render bobbafett
		m_bobbafett.Render();
		m_bobbafett2.Render();
		//Render Outside Walls
		backWall.Render();
		frontWall.Render();
		leftSide.RenderSide();
		rightSide.RenderSide();

		//render stonewall
		m_stonewall.Render();

		//Render section1 x walls from array
		for (int i= 0; i<section1xwall.size();i++)
		{
			section1xwall[i].RenderXWall();
		}

		//Render section 1 y walls from array
		for (int i = 0; i < section1ywall.size(); i++)
		{
			section1ywall[i].RenderYWall();
		}

		//Render section 2 x walls from array
		for (int i = 0; i < section2xwall.size(); i++)
		{
			section2xwall[i].RenderXWall();
		}

		//Render section 2 y walls from array
		for (int i = 0; i < section2ywall.size(); i++)
		{
			section2ywall[i].RenderYWall();
		}

		//Render section 3 x walls from array
		for (int i = 0; i < section3xwall.size(); i++)
		{
			section3xwall[i].RenderXWall();
		}

		//Render section 3 y walls from array
		for (int i = 0; i < section3ywall.size(); i++)
		{
			section3ywall[i].RenderYWall();
		}

		//Render section 4 x walls from array
		for (int i = 0; i < section4xwall.size(); i++)
		{
			section4xwall[i].RenderXWall();
		}

		//Render section 4 y walls from array
		for (int i = 0; i < section4ywall.size(); i++)
		{
			section4ywall[i].RenderYWall();
		}

		//m_fx.ActivateFog(0.02, 0.6, 0.6, 0.6);

		//Render Freddie mesh
		m_freddie.Render();

		glDisable(GL_LIGHTING);
		glColor3f(1, 1, 0);
		glPushMatrix();
		{
			glTranslatef(100,100,200);
			glutSolidSphere(25, 25, 25);
		}
		glPopMatrix();
		glEnable(GL_LIGHTING);
		
		m_hands.Render();

		//render cubes from Vector array
		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		cubes[0].SetPosition(CVector3f(0, 2, 0));
		glTranslatef(0, 2, 0);
		glScalef(0.25f, 0.25f, 0.25f);
		cubes[0].Render(1.0f, 0.0f, 0.0f, 0.0f);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glEnable(GL_BLEND);
		//2nd cube from vector array
		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		cubes[1].SetPosition(CVector3f(10, 2, 0));
		glTranslatef(10, 2, 0);
		glScalef(0.25f, 0.25f, 0.25f);
		cubes[1].Render(1.0f, 0.0f, 0.0f, 0.0f);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glPopMatrix();
		//3rd cube from vector array
		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		cubes[2].SetPosition(CVector3f(20, 2, 0));
		glTranslatef(20, 2, 0);
		glScalef(0.25f, 0.25f, 0.25f);
		cubes[2].Render(1.0f, 0.0f, 0.0f, 0.0f);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glPopMatrix();
		//4th cube from vector array
		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		cubes[3].SetPosition(CVector3f(30, 2, 0));
		glTranslatef(30, 2, 0);
		glScalef(0.25f, 0.25f, 0.25f);
		cubes[3].Render(1.0f, 0.0f, 0.0f, 0.0f);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glPopMatrix();
		//5th cube from vector array
		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		cubes[4].SetPosition(CVector3f(40, 2, 0));
		glTranslatef(40, 2, 0);
		glScalef(0.25f,0.25f,0.25f);
		cubes[4].Render(1.0f, 0.0f, 0.0f, 0.0f);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glPopMatrix();
		//6th cube from vector array
		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		cubes[5].SetPosition(CVector3f(50, 2, 0));
		glTranslatef(50, 2, 0);
		glScalef(0.25f, 0.25f, 0.25f);
		cubes[5].Render(1.0f, 0.0f, 0.0f, 0.0f);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glPopMatrix();
		//7th cube from vector array
		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		cubes[6].SetPosition(CVector3f(60, 2, 0));
		glTranslatef(60, 2, 0);
		glScalef(0.25f, 0.25f, 0.25f);
		cubes[6].Render(1.0f, 0.0f, 0.0f, 0.0f);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glPopMatrix();
		//8th cube from vector array
		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		cubes[7].SetPosition(CVector3f(70, 2, 0));
		glTranslatef(70, 2, 0);
		glScalef(0.25f, 0.25f, 0.25f);
		cubes[7].Render(1.0f, 0.0f, 0.0f, 0.0f);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glPopMatrix();
		//9th cube from vector array
		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		cubes[8].SetPosition(CVector3f(80, 2, 0));
		glTranslatef(80, 2, 0);
		glScalef(0.25f, 0.25f, 0.25f);
		cubes[8].Render(1.0f, 0.0f, 0.0f, 0.0f);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glPopMatrix();
		//10th cube from vector array
		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		cubes[9].SetPosition(CVector3f(90, 2, 0));
		glTranslatef(90, 2, 0);
		glScalef(0.25f, 0.25f, 0.25f);
		cubes[9].Render(1.0f, 0.0f, 0.0f, 0.0f);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glPopMatrix();

		for (int i = 0; i < m_numBolts; i++)
			m_lightningBolts[i].Render();
		
		glDisable(GL_LIGHTING);
		m_crossFade.Render(1, 0, 0);
		
		glEnable(GL_LIGHTING);

	}
	SwapBuffers(m_GameWindow.GetHdc());		
}

void Game::GameLoop()
{
	/*
	// This code implements a fixed timer
	m_dt = m_highResolutionTimer.Elapsed();

	if (m_dt > frame_duration) {
		m_highResolutionTimer.Start();

		Update();
		Render();
	}
	*/

	// This code implements a variable timer
	m_highResolutionTimer.Start();
	Update();
	Render();
	m_dt = m_highResolutionTimer.Elapsed();
			

}

WPARAM Game::Execute() 
{
	m_GameWindow.Init(m_hinstance);

	if(!m_GameWindow.GetHdc()) {
		return 1;
	}

	Initialise();

	m_highResolutionTimer.Start();

	double frame_duration = 1.0 / (double) 30.0;  // 30 FPS

	MSG msg;

	while(1) {													
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { 
			if(msg.message == WM_QUIT) {
				break;
			}

			TranslateMessage(&msg);	
			DispatchMessage(&msg);
		}else{
			GameLoop();
		} 
	}

	m_GameWindow.Deinit();

	return(msg.wParam);
}



LRESULT Game::ProcessEvents(HWND window,UINT message, WPARAM w_param, LPARAM l_param) 
{
	LRESULT result = 0;

	switch (message) {
	case WM_SIZE:
		if (!m_GameWindow.GetFullScreen()) {
			m_GameWindow.SizeOpenGLScreen(LOWORD(l_param), HIWORD(l_param));

			RECT dimensions;
			GetClientRect(window, &dimensions);
			m_GameWindow.SetDimensions(dimensions);
		}
		break;
 
	case WM_CHAR:
		switch (w_param) {
			case '0': {
				// respond to user pressing 0 key
				
				m_fx.DeactivateFog();
			}
			break;
			case '1': {
				// respond to user pressing 1 key
				//m_player.Turn(5.0f);
			}
			break;
			case '2': {
				// respond to user pressing 2 key
				//m_player.Turn(-5.0f);
			}
			break;
			case '3': {
				//Player attack
				//m_player.Attack();
			}
					  break;
			case 'm': {
				m_introScreen = false;
				//Sets the player moving at 5.0f
				//m_player.SetSpeed(5.0f);
			}
					  break;
			case '4': {
				m_fireball.Throw(m_camera);
			}
					  break;
			case '5': {
				for (int i = 0; i < m_numBolts; i++) {
					m_lightningBolts[i].Activate();
					//m_lightningBolts[i].ComputePath(CVector3f(50,2,50), CVector3f(0, 0, 1));
					m_lightningBolts[i].ComputePath(m_dragon1.GetPosition(),m_camera.GetPosition());
				}
			}
					  break;
					  /*
			case 's': {
				m_player.SetSpeed(0.0f);
			}
					  break;

			
			case 'w': {
				m_player.SetSpeed(5.0f);
			}
					  break;
			case 'd': {
				m_player.Strafe(m_dt * 10.0f);
				m_player.SetSpeed(0.0f);
			}
					  break;
			case 'a': {
				m_player.Strafe(m_dt * -10.0f);
				m_player.SetSpeed(0.0f);
			}
					  break;*/
		}
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(window, &ps);
		EndPaint(window, &ps);
		break;

	case WM_KEYDOWN:
		switch(w_param) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case VK_SPACE:
			m_animation++;
			//m_yohko.SetAnimation(m_animation);
			break;
		case VK_LBUTTON:
			m_fireball.Throw(m_camera);
			break;
		}
		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		result = DefWindowProc(window, message, w_param, l_param);
		break;
	}

	return result;
}

Game& Game::GetInstance() 
{
	static Game instance;

	return instance;
}

void Game::SetHinstance(HINSTANCE hinstance) 
{
	m_hinstance = hinstance;
}


LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
	return Game::GetInstance().ProcessEvents(window, message, w_param, l_param);
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, PSTR, int) 
{
	Game &game = Game::GetInstance();
	game.SetHinstance(hinstance);

	return game.Execute();
}
