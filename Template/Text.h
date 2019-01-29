#pragma once

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include ".\include\glut.h"	
#include <Windows.h>
#include <string>

class CText
{
public:
	CText();
	~CText();
	void Render(char *text, float x, float y, float r, float g, float b);
	//void RenderScore(int string , float x, float y, float r, float g, float b);
	void Create(HDC hdc, char *fontName, int size);
	void ResetPerspectiveProjection();
private:
	void SetOrthographicProjection();
	
	void RenderBitmapString(float x, float y, char *string);
	DWORD m_listBase;
	static DWORD m_listBaseCount;
};

