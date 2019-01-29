#include "CFreddie.h"



CFreddie::CFreddie()
{
	m_isActive = true;
}


CFreddie::~CFreddie()
{
	this->m_isActive = false;
	m_bbox.SetSize(0.0f,0.0f,0.0f);
}

void CFreddie::Initialise(CVector3f p)
{
	m_position = p;
	m_mesh.Load("Resources\\Meshes\\leet1.obj");
	m_bbox.SetSize(2.5f, 4.0f, 2.5f);
	m_bbox.SetBottom(m_position);
}

CBoundingBox CFreddie::GetBBox()
{
	return m_bbox;
}

CVector3f CFreddie::GetPosition() const
{
	return m_position;
}

void CFreddie::Update(float dt, CVector3f playerPos)
{

}

void CFreddie::Render()
{
	//Render Freddie
	glPushMatrix();
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glScalef(0.05,0.05,0.05);
	m_mesh.Render();
	glPopMatrix();

#if(_DEBUG)
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	m_bbox.Render(1, 1, 0.5);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
#endif // (_DEBUG)


}
