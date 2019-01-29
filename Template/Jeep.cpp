#include "Jeep.h"



CJeep::CJeep()
{
}


CJeep::~CJeep()
{
}

void CJeep::Initialise(CVector3f p)
{
	m_position = p;
	m_mesh.Load("Resources\\Meshes\\jeep1.obj");
	m_bbox.SetSize(5.0f,2.5f,7.0f);
	m_bbox.SetBottom(m_position);
}

CBoundingBox CJeep::GetBBox()
{
	return m_bbox;
}

CVector3f CJeep::GetPosition() const
{
	return m_position;
}

void CJeep::Render()
{
	//Render the jeep
	glPushMatrix();
	glTranslatef(m_position.x, m_position.y, m_position.z + (-1.5f));
	m_mesh.Render();
	glPopMatrix();

#if(_DEBUG)
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	m_bbox.Render(1, 0.5, 0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
#endif // (_DEBUG)
}
