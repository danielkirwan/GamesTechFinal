#include "Tetrahedron.h"
#include <Windows.h>
#include ".\include\glew.h"
#include ".\include\GL.H"
#include "Texture.h"

CTetrahedron::CTetrahedron(){}

CTetrahedron::~CTetrahedron() {}

void CTetrahedron::Initialise()
{
	// Load the texture
	CTexture texture;
	texture.Load("Resources\\Textures\\rock.bmp", false);
	m_textureID = texture.m_textureID;
}

void CTetrahedron::Render(float r, float g, float b, float a)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glColor4f(1.0, 1.0, 1.0, 1.0);


	GLfloat v0[3] = { -10,0,-10 };
	GLfloat v1[3] = { 10,0,-10 };
	GLfloat v2[3] = { 0,0,10 };
	GLfloat v3[3] = { 0,10,0 };
	//GLfloat v4[4] = {0,0,-10};

	glBegin(GL_TRIANGLES);
	//front
	//glColor4f(1.0, 1.0, 0.5, a);
	glTexCoord2f(0,0);
	glVertex3fv(v0);
	glTexCoord2f(1, 0);
	glVertex3fv(v2);
	glTexCoord2f(0.5, 1);
	glVertex3fv(v3);

	//left
	//glColor4f(r, g, b,a);
	glTexCoord2f(1, 0);
	glVertex3fv(v0);
	glTexCoord2f(0.5, 1);
	glVertex3fv(v3);
	glTexCoord2f(0, 0);
	glVertex3fv(v1);

	//right
	glTexCoord2f(0, 0);
	glVertex3fv(v2);
	glTexCoord2f(1, 0);
	glVertex3fv(v1);
	glTexCoord2f(0.5, 1);
	glVertex3fv(v3);

	//botton
	glTexCoord2f(0, 0);
	glVertex3fv(v0);
	glTexCoord2f(0, 0);
	glVertex3fv(v2);
	glTexCoord2f(0, 0);
	glVertex3fv(v1);


	glEnd();

}