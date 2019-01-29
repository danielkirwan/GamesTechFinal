#include "LightningBolt.h"
#include ".\include\glut.h"								// Header File For the GLu32 Library


CLightningBolt::CLightningBolt()
{
	m_isActive = false;
}

CLightningBolt::~CLightningBolt()
{}

void CLightningBolt::Activate()
{
	m_isActive = true;
	m_elapsedTime = 0.0f;
	m_totalTime = 1.0f; // run the effect for one second -- could pass this in instead
}


// Update the crossface based on elapsed time
void CLightningBolt::Update(float dt)
{

	if (m_isActive == false)
		return;

	// See if we should stop the effect
	m_elapsedTime += dt;
	if (m_elapsedTime > m_totalTime)
		m_isActive = false;

}

bool CLightningBolt::ComputePath(CVector3f p0, CVector3f dir)
{
	if (m_isActive == false)
		return false;

	m_points.clear();
	m_points.push_back(p0);
	CVector3f d = dir;
	for (int i = 1; i < 10; i++) {
		int hi = rand();
		float r1 = (rand() / (float)RAND_MAX) * 2.0f - 1.0f;
		float r2 = (rand() / (float)RAND_MAX) * 2.0f - 1.0f;
		float r3 = (rand() / (float)RAND_MAX) * 2.0f - 1.0f;
		float r4 = (rand() / (float)RAND_MAX) * 2.0f - 1.0f;

		CVector3f p = m_points[i - 1] + 3 * dir *(1 + r4) + CVector3f(r1, r2, r3) * 0.5;
		m_points.push_back(p);

		d = m_points[i] - m_points[i - 1];
		d.Normalise();
	}

	return true;
}

void CLightningBolt::RenderLineSegment(CVector3f p0, CVector3f p1, float alpha, CVector3f colour)
{


	for (int i = 1; i < 10; i += 2) {
		glLineWidth(i);
		float f = i / 10.0f;
		glColor4f(colour.x, colour.y, colour.z, .1*(1 - f)*alpha);
		glBegin(GL_LINES);
		glVertex3f(p0.x, p0.y, p0.z);
		glVertex3f(p1.x, p1.y, p1.z);
		glEnd();
	}
}

void CLightningBolt::Render()
{
	if (m_isActive == false)
		return;


	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDepthMask(GL_FALSE);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	for (int i = 0; i < (int)m_points.size() - 1; i++)
		RenderLineSegment(m_points[i], m_points[i + 1], 1, CVector3f(1, 1, 1));


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

}