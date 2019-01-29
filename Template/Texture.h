#pragma once

#include <windows.h>									// Header File For The Windows Library
#include <stdio.h>										// Header File For The Standard Input/Output Functions
#include <stdlib.h>										// Header File For The Standard Library
#include ".\include\glew.h"
#include <math.h>										// Header File For The Math header file
#include ".\include\GL.H"											// Header File For The OpenGL32 Library
#include ".\include\glu.h"									// Header File For The GLu32 Library
#include ".\include\glaux.h"	
// Header File For The Glaux Library

#include <vector>

using namespace std;



class CTexture
{
public:
	CTexture();
	~CTexture();
	bool Load(string sPath, bool clamp);
	void CreateFromRGB(unsigned char r, unsigned char g, unsigned char b);
	void CreateFromData(BYTE* bData, int iWidth, int iHeight, int iBPP, GLenum format, bool clamp);
	void Bind();
	
	GLuint m_textureID;
	string m_sPath;

	unsigned int m_width;
	unsigned int m_height;


};