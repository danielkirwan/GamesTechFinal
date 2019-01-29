#include "Cube.h"
#include <Windows.h>

#include "./include/glut.h"
#include "Texture.h"
#include "Player.h"
#include "Vector3f.h"

CCube::CCube(){}
CCube::~CCube(){}

void CCube::Initialise(CVector3f p) 
{

	m_isActive = true;
	m_CubeTheta = 0;
	m_cubePosition = p;
	cube_score = 10;
	CTexture texture;
	texture.Load("Resources\\Textures\\brick.bmp", false);
	m_textureID = texture.m_textureID;
	m_audio.Initialise();
	m_audio.LoadEventSound("Resources\\Audio\\pickup1.wav");
}

void CCube::InitialiseWall(int width, int height, int depth)
{
	m_isActive = true;
	CTexture texture;
	texture.Load("Resources\\Textures\\rock.bmp", false);
	m_textureID = texture.m_textureID;
}


CVector3f CCube::GetPosition()const
{
	return m_cubePosition;
}

void CCube::SetPosition(CVector3f setPos)
{
	m_cubePosition = setPos;
}


UINT CCube::GetTextureID()
{
	return m_textureID;
}


//Update the cube with the playerPosition, the time passed, the game score and the current cube position
void CCube::Update(CVector3f c, float dt, CScore *score, CVector3f cubePos) 
{
	m_CubeTheta += dt * 50.0f;
	cube_score;

	float scalarResult;
	//CVector3f q = m_cubePosition;
	CVector3f q = cubePos;
	CVector3f t = q - c;
	scalarResult = t.Length();

	if (scalarResult < 3.0f)
	{
		if (m_isActive)
			score->Update(cube_score + score->m_score);
			m_audio.PlayEventSound();
		this->m_isActive = false;
	}
}



void CCube::Render(float r, float g, float b, float a)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	//Vector points for Cube render
	GLfloat v1[3] = {-1,1,1  };		//top left front face		//top-right of left face
	GLfloat v2[3] = { -1,-1,1 };	//bottom left front face	//bottom-left of bottom face		//bottom-right of left face
	GLfloat v3[3] = { 1,-1,1 };		//bottom right front face	//bottom-right of bottom face
	GLfloat v4[3] = { 1,1,1 };		//top right front face		//bottom-right of top face
	GLfloat v4r[3] = { 1,1,-1 };	//top left right face
	GLfloat v5[3] = {1,1,1};		//top right right face
	GLfloat v6[3] = { 1,-1,1 };		//bottom right right face
	GLfloat v3r[3] = { 1,-1,-1 };	//bottom left of right face
	GLfloat v1t[3] = { -1,1,1 };	// Bottom-left of top face
	GLfloat v5t[3] = {1,1,-1};		//top-right of top face		//top-left  of back face
	GLfloat v7[3] = { -1,1,-1 };	//top-left of top face		//top-left of left face				//top-right of back face
	GLfloat v8[3] = { -1,-1,-1 };	//top-left of bottom face	//bottom-left of left face
	GLfloat v6b[3] = { 1,-1,-1 };	//top-right of bottom face	//bottom-left of back face


	//Vectors for the cube
	CVector3f p1 = CVector3f(v1[0], v1[1], v1[2]);		//top left front face		//top-right of left face
	CVector3f p2 = CVector3f(v2[0],v2[1],v2[2]);	//bottom left front face	//bottom-left of bottom face		//bottom-right of left face
	CVector3f p3 = CVector3f(v3[0],v3[1],v3[2]);		//bottom right front face	//bottom-right of bottom face
	CVector3f p4 = CVector3f(v4[0],v4[1],v4[2]);		//top right front face		//bottom-right of top face
	CVector3f p4r = CVector3f(v4r[0],v4r[1],v4r[2]);	//top left right face
	CVector3f p5 = CVector3f(v5[0],v5[1],v6[2]);		//top right right face
	CVector3f p6 = CVector3f(v6[0],v6[1],v6[2]);		//bottom right right face
	CVector3f p3r = CVector3f(v3r[0],v3r[1],v3r[2]);	//bottom left of right face
	CVector3f p1t = CVector3f(v1t[0],v1t[1],v1t[2]);	// Bottom-left of top face
	CVector3f p5t = CVector3f(v5t[0],v5t[1],v5t[2]);	//top-right of top face		//top-left  of back face
	CVector3f p7 = CVector3f(v7[0],v7[1],v7[2]);	//top-left of top face		//top-left of left face				//top-right of back face
	CVector3f p8 = CVector3f(v8[0],v8[1],v8[2]);	//top-left of bottom face	//bottom-left of left face
	CVector3f p6b = CVector3f(v6b[0],v6b[1],v6b[2]);	//top-right of bottom face	//bottom-left of back face

	//How to do cross product
	//Top face normals
	CVector3f xp1 = p4 - p1t;
	CVector3f xp2 = p7 - p1t;
	CVector3f cp1t = xp1 % xp2;
	cp1t.Normalise();
	xp1 = p5t - p4;
	xp2 = p1t - p4;
	CVector3f cp4 = xp1 % xp2;
	cp4.Normalise();
	xp1 = p7 - p5t;
	xp2 = p4 - p5t;
	CVector3f cp5t = xp1 % xp2;
	cp5t.Normalise();
	xp1 = p5t - p7;
	xp2 = p1t - p7;
	CVector3f cp7 = xp1 % xp2;
	cp7.Normalise();
	//Bottom face normals
	xp1 = p6b - p8;
	xp2 = p2 - p8;
	CVector3f cp8 = xp1 % xp2;
	cp8.Normalise();
	xp1 = p3 - p6b;
	xp2 = p8 - p6b;
	CVector3f cp6b = xp1 % xp2;
	cp6b.Normalise();
	xp1 = p2 - p3;
	xp2 = p6b - p3;
	CVector3f cp3 = xp1 % xp2;
	cp3.Normalise();
	xp1 = p8 - p2;
	xp2 = p3 - p2;
	CVector3f cp2 = xp1 % xp2;
	//Left face normals
	xp1 = p2 - p8;
	xp1 = p7 - p8;
	CVector3f cp82 = xp1 % xp2;
	cp82.Normalise();
	xp1 = p1 - p2;
	xp2 = p8 - p2;
	CVector3f cp22 = xp1 % xp2;
	cp2.Normalise();
	xp1 = p7 - p1;
	xp2 = p2 - p1;
	CVector3f cp1 = xp1 % xp2;
	cp1.Normalise();
	xp1 = p8 - p7;
	xp1 = p1 - p7;
	CVector3f cp71 = xp1 % xp2;
	//back face normals
	xp1 = p8 - p6b;
	xp2 = p5t - p6b;
	CVector3f cpvb2 = xp1 % xp2;
	cpvb2.Normalise();
	xp1 = p7 - p8;
	xp2 = p6b - p8;
	CVector3f cp823 = xp1 % xp2;
	cp823.Normalise();
	xp1 = p5t - p7;
	xp2 = p8 - p7;
	CVector3f cp72 = xp1 % xp2;
	cp72.Normalise();
	xp1 = p6b - p5t;
	xp2 = p7 - p5t;
	CVector3f cp5t2 = xp1 % xp2;
	cp5t2.Normalise();
	//right face normals
	xp1 = p5 - p4r;
	xp2 = p3r - p4r;
	CVector3f cp4r = xp1 % xp2;
	cp4r.Normalise();
	xp1 = p6 - p5;
	xp1 = p4r - p5;
	CVector3f cpv5 = xp1 % xp2;
	cpv5.Normalise();
	xp1 = p3r - p6;
	xp2 = p5 - p6;
	CVector3f cpv6 = xp1 % xp2;
	cpv6.Normalise();
	xp1 = p4r = p3r;
	xp2 = p6 - p3r;
	CVector3f cp3r = xp1 % xp2;
	cp3r.Normalise();
	//Front face normals
	xp1 = p3 - p2;
	xp2 = p1 - p2;
	CVector3f cpfbl = xp1 % xp2;
	cpfbl.Normalise();
	xp1 = p4 - p3;
	xp2 = p2 - p3;
	CVector3f cpfbr = xp1 % xp2;
	cpfbr.Normalise();
	xp1 = p1 - p4;
	xp2 = p3 - p4;
	CVector3f cpftr = xp1 % xp2;
	cpftr.Normalise();
	xp1 = p2 - p1;
	xp2 = p4 - p1;
	CVector3f cpftl = xp1 % xp2;
	cpftl.Normalise();
	//Cross produc end

	// Render a cube
	if (m_isActive) {

		//glTranslatef(m_cubePosition.x, m_cubePosition.y, m_cubePosition.z);

		glRotatef(m_CubeTheta, 1, 1, 0);

		glBegin(GL_QUADS);

		
		// Top face
		//glColor3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(0, 0);
		glNormal3f(cp1t.x, cp1t.y,cp1t.z);		//Vector normal
		glVertex3fv(v1t);  // Bottom-left of top face
		glTexCoord2f(1, 0);
		glNormal3f(cp4.x, cp4.y, cp4.z);		//Vector normal
		glVertex3fv(v4);  // Bottom-right of top face
		glTexCoord2f(1, 1);
		glNormal3f(cp5t.x, cp5t.y, cp5t.z);		//Vector normal
		glVertex3fv(v5t);  // Top-right of top face
		glTexCoord2f(0, 1);
		glNormal3f(cp7.x, cp7.y, cp7.z);		//Vector normal
		glVertex3fv(v7);  // Top-left of top face

		// Bottom face
		//glColor3f(1.0f, 0.0f, 1.0f);
		glTexCoord2f(0, 1);
		glNormal3f(cp8.x, cp8.y, cp8.z);		//Vector normal
		glVertex3fv(v8); // Top-left of bottom face
		glTexCoord2f(1, 1);
		glNormal3f(cp6b.x, cp6b.y, cp6b.z);		//Vector normal
		glVertex3fv(v6b); // Top-right of bottom face
		glTexCoord2f(1, 0);
		glNormal3f(cp3.x, cp3.y, cp3.z);		//Vector normal
		glVertex3fv(v3); // Bottom-right of bottom face
		glTexCoord2f(0, 0);
		glNormal3f(cp2.x, cp2.y, cp2.z);		//Vector normal
		glVertex3fv(v2); // Bottom-left of bottom face

		// Left face
		//glColor3f(1.0f, 0.0f, 0.0f); //Red
		glTexCoord2f(0, 0);
		glNormal3f(cp82.x, cp82.y, cp82.z);		//Vector normal
		glVertex3fv(v8);  // Bottom-Left of left face
		glTexCoord2f(1, 0);
		glNormal3f(cp22.x, cp22.y, cp22.z);		//Vector normal
		glVertex3fv(v2);  // Bottom-Right of left face
		glTexCoord2f(1, 1);
		glNormal3f(cp1.x, cp1.y, cp1.z);		//Vector normal
		glVertex3fv(v1);  // Top-Right of left face
		glTexCoord2f(0, 1);
		glNormal3f(cp71.x, cp71.y, cp71.z);		//Vector normal
		glVertex3fv(v7);  // Top-Left of left face 

		// Back face
		//glColor3f(0.0f, 1.0f, 0.0f);	//Green
		glTexCoord2f(0, 0);
		glNormal3f(cpvb2.x, cpvb2.y, cpvb2.z);		//Vector normal
		glVertex3fv(v6b); // Bottom-Left of back face
		glTexCoord2f(1, 0);
		glNormal3f(cp823.x, cp823.y, cp823.z);		//Vector normal
		glVertex3fv(v8); // Bottom-Right of back face
		glTexCoord2f(1, 1);
		glNormal3f(cp72.x, cp72.y, cp72.z);		//Vector normal
		glVertex3fv(v7); // Top-Right of back face
		glTexCoord2f(0, 1);
		glNormal3f(cp5t2.x, cp5t2.y, cp5t2.z);		//Vector normal
		glVertex3fv(v5t); // Top-Left of back face

		// Right face
		//glColor3f(0.0f, 0.0f, 1.0f); //Blue
		glTexCoord2f(0, 1);
		glNormal3f(cp4r.x, cp4r.y, cp4r.z);		//Vector normal
		glVertex3fv(v4r);  // Top-Left of right face
		glTexCoord2f(1, 1);
		glNormal3f(cpv5.x, cpv5.y, cpv5.z);		//Vector normal
		glVertex3fv(v5);  // Top-Right of right face
		glTexCoord2f(1, 0);
		glNormal3f(cpv6.x, cpv6.y, cpv6.z);		//Vector normal
		glVertex3fv(v6);  // Bottom-Right of right face
		glTexCoord2f(0, 0);
		glNormal3f(cp3r.x, cp3r.y, cp3r.z);		//Vector normal
		glVertex3fv(v3r);  // Bottom-Left of right face

		// Front face
		//glColor3f(1.0f, 0.5f, 0.0f);	//Orange
		glTexCoord2f(0, 0);
		glNormal3f(cpfbl.x, cpfbl.y, cpfbl.z);		//Vector normal
		glVertex3fv(v2);  // Bottom-left of front face
		glTexCoord2f(1, 0);
		glNormal3f(cpfbr.x, cpfbr.y, cpfbr.z);		//Vector normal
		glVertex3fv(v3);  // Bottom-right of front face
		glTexCoord2f(1, 1);
		glNormal3f(cpftr.x, cpftr.y, cpftr.z);		//Vector normal
		glVertex3fv(v4);  // Top-Right of front face
		glTexCoord2f(0, 1);
		glNormal3f(cpftl.x, cpftl.y, cpftl.z);		//Vector normal
		glVertex3fv(v1);  // Top-left of front face

		glEnd();
	} 
}

