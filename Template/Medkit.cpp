#include "Medkit.h"



CMedkit::CMedkit()
{
	m_isActive = true;
}


CMedkit::~CMedkit()
{
	this->m_isActive = false;
}

void CMedkit::Initialise(CVector3f pos)
{
	m_position = pos;
	healthIncrease = 50;
	m_mesh.Load("Resources\\Meshes\\medkit\\medkit.obj");
	m_bbox.SetSize(2.0f, 0.2f, 2.0f);
	m_bbox.SetBottom(m_position);
}

void CMedkit::Update(CVector3f c, CHealth *health , float dt, CVector3f medkitPos)
{
	//m_CubeTheta += dt * 50.0f;
	float scalarResult;
	CVector3f q = medkitPos;
	CVector3f t = c - q;
	scalarResult = t.Length();

	healthIncrease;

	if (scalarResult < 5.0f)
	{
		if (m_isActive)
			health->Update(healthIncrease + health->m_health);
		this->m_isActive = false;
	}
	m_bbox.SetBottom(m_position);
}

CVector3f CMedkit::GetPosition() const
{
	return m_position;
}

void CMedkit::SetPosition(CVector3f setPos)
{
	m_position = setPos;
}

void CMedkit::Render()
{
	if(m_isActive){
	glPushMatrix();
	glTranslatef(m_position.x, m_position.y, m_position.z);
	//glRotatef(m_CubeTheta, 1, 1, 0);
	m_mesh.Render();
	glPopMatrix();

	#if(_DEBUG)
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	m_bbox.Render(1, 0, 0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	}

#endif
}

CBoundingBox CMedkit::GetBBox()
{
	return m_bbox;
}
