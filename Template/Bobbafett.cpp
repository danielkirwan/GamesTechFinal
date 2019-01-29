#define _USE_MATH_DEFINES								// Will allow certain constants (like M_PI) to be availabe from <math.h>

#include <windows.h>									// Header File For the Windows Library
#include <stdio.h>										// Header File For the Standard Input/Output Functions
#include <stdlib.h>										// Header File For the Standard Library
#include <math.h>										// Header File For the Math header file
#include ".\include\glew.h"								// Header File For the GLEW Library
#include ".\include\GL.H"								// Header File For the OpenGL32 Library
#include ".\include\glu.h"								// Header File For the GLu32 Library
#include "Bobbafett.h"

CBobbafett::CBobbafett()
{
	//m_direction = CVector3f(1, 0, 0); Original position
	m_direction = CVector3f(1, 0, 0);
	m_speed = 0.0f;
	health = 2;
	m_isActive = true;
}

CBobbafett::~CBobbafett()
{ 
	this->m_isActive = false;
	this->m_bbox.SetSize(0, 0, 0);
}

void CBobbafett::Initialise(CVector3f p)
{
	m_position = p;
	m_mesh.Load("Resources\\Meshes\\bobbafett.md2", "Resources\\Meshes\\bobbafett.bmp", "Resources\\Meshes\\bobbafettWeapon.md2", "Resources\\Meshes\\bobbafettWeapon.bmp");
	m_bbox.SetBottom(m_position);
	m_bbox.SetSize(1.0f, 2.4f, 1.0f);
}

void CBobbafett::Update(float dt, CVector3f playerPos)
{
	float scalarResult;
	CVector3f p = playerPos;

	CVector3f dis = m_position - p;
	scalarResult = dis.Length();

	if (scalarResult < 10.0f)
	{
		Attack();
	}
	else if (scalarResult > 10.0f)
	{
		Advance(1.0f * dt);
	}
	else {
		Stand();
	}

	m_bbox.SetBottom(m_position);
}

void CBobbafett::Render()
{
	m_isActive = true;
	glPushMatrix();	float scalarResult;
	glTranslatef(m_position.x, 1.2f, m_position.z);
	scalarResult = atan2(m_direction.z, m_direction.x);
	scalarResult = scalarResult * (180.0f / M_PI);

	//Class didn't recognise the AI_RAD_TO_DEG so used the above equation
	//scalarResult = AI_RAD_TO_DEG(scalarResult);

	//Needs to be a minus as rotating clockwise
	glRotatef(-scalarResult, 0, 1.0f, 0);
	//glTranslatef(0, 1, -15);
	glScalef(0.05f, 0.05f, 0.05f);
	m_mesh.Render(true);
	glPopMatrix();

#if(_DEBUG)
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	m_bbox.Render(0.5, 0.5, 0.5);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

#endif

}

CVector3f CBobbafett::GetPosition() const
{
	return m_position;
}

void CBobbafett::Attack()
{
	m_mesh.SetAnimation(ATTACK);
	m_speed = 0.0f;
}

void CBobbafett::Advance(float speed)
{
	m_mesh.SetAnimation(RUN);
	m_speed = 5.0f;

	float c = 15;
	CVector3f v = m_position + c * m_direction;
	CVector3f view = v - m_position;
	view.Normalise();

	m_position += view * speed;
	v += view * speed;
}

void CBobbafett::SetSpeed(float speed)
{

}

void CBobbafett::Stand()
{
	m_mesh.SetAnimation(STAND);
	m_speed = 0.0f;
}

CBoundingBox CBobbafett::GetBBox()
{
	return m_bbox;
}

bool CBobbafett::IsActive(bool isactive)
{
	return isactive;
}
