#include "Dragon.h"



CDragon::CDragon()
{
	m_isActive = true;
}


CDragon::~CDragon()
{
	this->m_isActive = false;
	m_bbox.SetSize(0,0,0);
}

void CDragon::Initialise(CVector3f p)
{
	m_position = p;
	m_mesh.Load("Resources\\Meshes\\Dragon\\dragon.obj");
	m_bbox.SetSize(5.0f, 5.0f,5.0f);
	m_bbox.SetBottom(m_position);
}

CBoundingBox CDragon::GetBBox()
{
	return m_bbox;
}

CVector3f CDragon::GetPosition() const
{
	return m_position;
}

void CDragon::Render()
{
	//Render Dragon
	glPushMatrix();
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glScalef(10,10,10);
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
