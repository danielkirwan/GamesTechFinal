#include "Xenoid.h"



CXenoid::CXenoid()
{

	m_direction = CVector3f(0, 0, 1);
	m_speed = 0.0f;
	health = 2;
	m_isActive = true;
}


CXenoid::~CXenoid()
{
	this->m_isActive = false;
	this->m_bbox.SetSize(0,0,0);
}

void CXenoid::Update(float dt, CVector3f playerPos)
{
	float scalarResult;
	float ScalarResult2;
	CVector3f p = playerPos;

	CVector3f enemyPos = m_position;
	CVector3f distance = p - enemyPos;
	ScalarResult2 = atan2(distance.x, distance.z);
	ScalarResult2 = AI_RAD_TO_DEG(ScalarResult2);

	

	CVector3f dis = m_position - p;
	scalarResult = dis.Length();

	if (scalarResult < 10.0f)
	{
		Attack();
		glRotatef(-ScalarResult2, 0, 1.0f, 0);
	}
	else if (scalarResult > 10.0f)
	{
		Advance(1.0f * dt);
	}


	m_bbox.SetBottom(m_position);
}

void CXenoid::Initialise(CVector3f p)
{
	m_position = p;
	//Initialising the mesh for the player
	m_mesh.Load("./Resources/Meshes/xenoid/tris.md2", "./Resources/Meshes/xenoid/xenotype1.bmp",
		"./Resources/Meshes/xenoid/weapon.md2", "./Resources/Meshes/xenoid/weapon.bmp");
	//setting the animation that will be initially run
	m_mesh.SetAnimation(RUN);
	m_bbox.SetBottom(m_position);
	m_bbox.SetSize(1.0f, 2.4f, 1.0f);
}

void CXenoid::Render()
{
	if(m_isActive)
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
	}
#if(_DEBUG)
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	m_bbox.Render(1, 0, 0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

#endif
}

CVector3f CXenoid::GetPosition() const
{
	return m_position;
}

void CXenoid::Turn(float angle)
{
	
}

void CXenoid::Attack()
{
	m_mesh.SetAnimation(ATTACK);
	m_speed = 0.0f;
}

void CXenoid::Advance(float speed)
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

void CXenoid::SetSpeed(float speed)
{
	m_speed = speed;
}

void CXenoid::Stand()
{
	m_mesh.SetAnimation(STAND);
	m_speed = 0.0f;
}

void CXenoid::SetPosition(CVector3f setPos)
{
	m_position = setPos;
}

CBoundingBox CXenoid::GetBBox()
{
	return m_bbox;
}
