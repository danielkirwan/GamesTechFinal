#pragma once
#include ".\include\glew.h"
#include ".\include\GL.H"
#include <Windows.h>
#include "Text.h"

class CScore
{
public:
	CScore();							//Constructor
	~CScore();							//Destructor
	void Initialise(int score);			//Score initialise function
	void Update(int score);				//Score Update function
	void Render();						//Render object

	int m_score;						//Create Score variable

	CText m_text;						//Create text variable 
};
