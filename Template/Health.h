#pragma once
#include ".\include\glew.h"
#include ".\include\GL.H"
#include <Windows.h>
#include "Text.h"
class CHealth
{
public:
	CHealth();
	~CHealth();
	void Initialise(int health);			//Score initialise function
	void Update(int health);				//Score Update function
	void Render();						//Render object

	int m_health;						//Create Score variable

	CText m_text;						//Create text variable 
};

