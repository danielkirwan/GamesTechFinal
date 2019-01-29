#define _USE_MATH_DEFINES								// Will allow certain constants (like M_PI) to be availabe from <math.h>

#include <windows.h>									// Header File For the Windows Library
#include <stdio.h>										// Header File For the Standard Input/Output Functions
#include <stdlib.h>										// Header File For the Standard Library
#include <math.h>										// Header File For the Math header file
#include ".\include\glew.h"								// Header File For the GLEW Library
#include ".\include\GL.H"								// Header File For the OpenGL32 Library
#include ".\include\glu.h"								// Header File For the GLu32 Library
#include "Player.h"



CPlayer::CPlayer()
{
	m_position = m_camera.GetPosition();
	//m_direction = CVector3f(1, 0, 0); Original position
	m_direction = CVector3f(0, 0, 1);
	m_speed = 0.0f;
}
CPlayer::~CPlayer(){}

void CPlayer::Initialise()
{
	//Initialising the mesh for the player
	m_mesh.Load("./Resources/Meshes/Yohko.md2", "./Resources/Meshes/Yohko.bmp",
				"./Resources/Meshes/YohkoWeapon.md2", "./Resources/Meshes/YohkoWeapon.bmp");
	//setting the animation that will be initially run
	m_mesh.SetAnimation(YOHKO_RUN);
	m_bbox.SetBottom(m_position);
	m_bbox.SetSize(1.0f, 2.4f, 1.0f);
}

void CPlayer::Update(float dt)
{

	m_position += m_direction * m_speed * dt;
	//Changing animation from attack to run if the last frame of the attack animation has run
	if (m_mesh.GetAnimation() == YOHKO_ATTACK && m_mesh.IsLastFrameRendered())
	{
		m_mesh.SetAnimation(YOHKO_RUN);
		m_speed = 5.0f;
	}
	m_bbox.SetBottom(m_position);
}

//Added so I can set the speed in the game.cpp file
void CPlayer::SetSpeed(float speed)
{
	m_speed = speed;
}

void CPlayer::Render()
{
	glPushMatrix();
		float scalarResult;
		glTranslatef(m_position.x, 1.2f, m_position.z);

		scalarResult = atan2(m_direction.z, m_direction.x);
		scalarResult = scalarResult * (180.0f / M_PI);

		//Class didn't recognise the AI_RAD_TO_DEG so used the above equation
		//scalarResult = AI_RAD_TO_DEG(scalarResult);

		//Needs to be a minus as rotating clockwise
		glRotatef(-scalarResult, 0, 1.0f, 0);

		glScalef(0.05f, 0.05f, 0.05f);
		m_mesh.Render(true);
	glPopMatrix();

#if(_DEBUG)
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	m_bbox.Render(1, 0, 0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

#endif
}

void CPlayer::UpdateCamera(Camera &camera, double dt)
{
	//Puts the camers behind the player and moves with the player
	float a = 5, b = 10, c = 15;
	CVector3f viewport = m_position + c * m_direction;
	CVector3f position = m_position + CVector3f(0.0f, a, 0.0f) - b * m_direction;
	camera.Set(position, viewport, CVector3f(0.0f, 1.0f, 0.0f), 5.0f);

	//The below is going to be used for the strafe method but haven't figured out how to implement it correctly
	CVector3f m_upVector = CVector3f(0.0f, 1.0f, 0.0f);
	m_strafeVector = (viewport - m_position) % m_upVector;
	m_strafeVector.Normalise();

	Movement(dt);

}

//Method to advance the player by using the Game::Process events method on key presses
//Can move forwards and backwards. 
void CPlayer::Advance(float speed)
{
	float c = 15;
	CVector3f v = m_position + c * m_direction;
	CVector3f view = v - m_position;
	view.Normalise();

	m_position += view * speed;
	v += view * speed;
}

//Allows thrid person player to strafe
void CPlayer::Strafe(float speed)
{
	m_position.x += m_strafeVector.x * speed;
	m_position.z += m_strafeVector.z * speed;

}

void CPlayer::Movement(double dt)
{
	float speed = (float)dt * m_speed;

	if ((GetKeyState(VK_UP) & 0x80 || GetKeyState('W') & 0x80)) {
			Advance(speed);
			m_mesh.SetAnimation(YOHKO_RUN);
	}

	if ((GetKeyState(VK_DOWN) & 0x80 || GetKeyState('S') & 0x80)) {
			Advance(-speed);
	}

	if ((GetKeyState(VK_LEFT) & 0x80 || GetKeyState('A') & 0x80)) {
		Strafe(-speed); // Left
	}

	if ((GetKeyState(VK_RIGHT) & 0x80 || GetKeyState('D') & 0x80)) {
		Strafe(speed); // Right
	}
}

void CPlayer::Turn(float angle)
{
	m_direction = m_direction.RotateAboutAxis(angle, CVector3f(0, 1, 0));
} 

void CPlayer::Attack()
{
	m_mesh.SetAnimation(YOHKO_ATTACK);
	m_speed = 0.0f;
}

void CPlayer::Stand()
{
	m_mesh.SetAnimation(YOHKO_STAND);
	m_speed = 0.0f;
}

void CPlayer::SetPosition(CVector3f setPos)
{
	m_position = setPos;
}

CBoundingBox CPlayer::GetBBox()
{
	return m_bbox;
}

CVector3f CPlayer::GetPosition() const
{
	return m_position;
}