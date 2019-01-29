#include "Diamond.h"
#include ".\include\glew.h"
#include ".\include\GL.H"
#include "Texture.h"



CDiamond::CDiamond()
{
}


CDiamond::~CDiamond()
{
}

void CDiamond::Initialise()
{
	// Load the texture
	CTexture texture;
	texture.Load("Resources\\Textures\\rock.bmp", false);
	m_textureID = texture.m_textureID;
}

void CDiamond::Render(float r, float g, float b, float a)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	GLfloat v0[3] = { 1,0,1 };
	GLfloat v1[3] = { 1,0,1 };
	GLfloat v2[3] = { 0,0,1 };
	GLfloat v3[3] = { 0,1,0 };
	GLfloat v4[3] = { 0,-1,0 };
	

	glBegin(GL_TRIANGLES);
	//front
	//glColor4f(1.0, 1.0, 0.5, a);
	glTexCoord2f(0, 0);
	glVertex3fv(v0);
	glTexCoord2f(1, 0);
	glVertex3fv(v2);
	glTexCoord2f(0.5, 1);
	glVertex3fv(v3);
	//front down
	glTexCoord2f(0.5, 1);
	glVertex3fv(v4);
	glTexCoord2f(0, 0);
	glVertex3fv(v0);
	glTexCoord2f(1, 0);
	glVertex3fv(v2);
	
	//left
	//glColor4f(r, g, b,a);
	glTexCoord2f(1, 0);
	glVertex3fv(v0);
	glTexCoord2f(0.5, 1);
	glVertex3fv(v3);
	glTexCoord2f(0, 0);
	glVertex3fv(v1);

	//left down
	glTexCoord2f(0, 0);
	glVertex3fv(v1);
	glTexCoord2f(1, 0);
	glVertex3fv(v0);
	glTexCoord2f(0.5, 1);
	glVertex3fv(v4);
	

	//right
	glTexCoord2f(0, 0);
	glVertex3fv(v2);
	glTexCoord2f(1, 0);
	glVertex3fv(v1);
	glTexCoord2f(0.5, 1);
	glVertex3fv(v3);

	//right down
	glTexCoord2f(0, 0);
	glVertex3fv(v2);
	glTexCoord2f(1, 0);
	glVertex3fv(v1);
	glTexCoord2f(0.5, 1);
	glVertex3fv(v4);

	glEnd();

}
