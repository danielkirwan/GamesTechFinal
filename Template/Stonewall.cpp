#include "Stonewall.h"



CStonewall::CStonewall()
{
}


CStonewall::~CStonewall()
{
}

void CStonewall::Initialise(CVector3f p)
{
	m_position = p;
	m_mesh.Load("Resources\\Meshes\\stonewall2.obj");
	//m_bbox.SetSize(40.0f, 7.5f, 7.0f);
	m_bbox.SetSize(100.0f, 7.5f, 7.0f);
	m_bbox.SetBottom(m_position);
}

CBoundingBox CStonewall::GetBBox()
{
	return m_bbox;
}

CVector3f CStonewall::GetPosition() const
{
	return m_position;
}

void CStonewall::Render()
{
	//Render the stonewall
	glPushMatrix();
	glTranslatef(m_position.x + (-14.0f), m_position.y, m_position.z + (-9.5f));
	glScalef(2.5f, 1.0f, 1.0f);
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
