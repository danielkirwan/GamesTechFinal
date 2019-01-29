#include "Wall.h"

CWall::CWall()
{
}

CWall::~CWall()
{
}

void CWall::Initialise(CVector3f p)
{
	m_position = p;
	m_mesh.Load("Resources\\Meshes\\wall2.obj");
	//Works for original scale of 10,10,5
	//m_bbox.SetSize(14, 6, 0.5);
	m_bbox.SetSize(700,6,0.5);
	m_bbox.SetBottom(m_position);
}

void CWall::Update()
{
	m_bbox.SetBottom(GetPosition());
}

void CWall::SetPosition(CVector3f setPos)
{
	m_position = setPos;
}

CBoundingBox CWall::GetBBox()
{
	return m_bbox;
}

CVector3f CWall::GetPosition() const
{
	return m_position;
}

void CWall::Render()
{
	//Render the wall
	glPushMatrix();
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glScalef(250.0f,10.0f,5.0f);
	m_mesh.Render();
	glPopMatrix();

#if(_DEBUG)
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	m_bbox.Render(1, 0, 0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
#endif // (_DEBUG)

}

void CWall::RenderSide()
{
	//Render the wall
	glPushMatrix();
	m_bbox.SetSize(0.5, 6, 700);
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glRotatef(270.0f,0.0f,-1.0f,0.0f);
	glScalef(250.0f, 10.0f, 5.0f);
	m_mesh.Render();
	glPopMatrix();

#if(_DEBUG)
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	m_bbox.Render(1, 0, 0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
#endif // (_DEBUG)
}

void CWall::RenderXWall()
{
	//Render the wall
	glPushMatrix();
	m_bbox.SetSize(14, 6, 0.5f);
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glScalef(10.0f, 10.0f, 5.0f);
	m_mesh.Render();
	glPopMatrix();

#if(_DEBUG)
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	m_bbox.Render(0, 0, 1);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
#endif // (_DEBUG)
}

void CWall::RenderYWall()
{
	//Render the wall
	glPushMatrix();
	m_bbox.SetSize(0.5f, 6.0f, 14.0f);
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	m_mesh.Render();
	glPopMatrix();

#if(_DEBUG)
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	m_bbox.Render(1, 1, 0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
#endif // (_DEBUG)
}











