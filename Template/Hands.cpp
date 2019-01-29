#include "Hands.h"



CHands::CHands()
{
}


CHands::~CHands()
{
}

void CHands::Initialise(CVector3f pos)
{
	m_mesh.Load("Resources\\meshes\\hands\\Half_Life_2_Rig.obj");
	m_position = pos;
}

void CHands::Render()
{
	glPushMatrix();
	glTranslatef(m_position.x,m_position.y,m_position.z);
	m_mesh.Render();
	glPopMatrix();
}
