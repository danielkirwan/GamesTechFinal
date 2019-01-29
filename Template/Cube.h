#pragma once
#include "Vector3f.h"
#include ".\include\glew.h"
#include ".\include\GL.H"
#include <Windows.h>
#include "Score.h"
#include "include/glut.h"
#include "Audio.h"

class CCube
{
public: 
	CCube();
	~CCube();
	void Initialise(CVector3f p);										//Initialise the cube class
	void Update(CVector3f c, float dt, CScore *score, CVector3f cubePos);	//Update the cube class
	CVector3f GetPosition() const;										//Get the cube position
	void SetPosition(CVector3f setPos);									//Set the cube position
	void Render(float r, float g, float b, float a);					//Render the cube
	double m_CubeTheta;													//For the angle to rotate the cube
	UINT GetTextureID();												//Not being utilised
	void InitialiseWall(int width, int height, int depth);
	
private:
	bool m_isActive;													//Used to make the cube disappear if player is within certain distance
	CVector3f m_cubePosition;											//Used to set/get the cube position
	UINT m_textureID;													//Texture ID for my texture
	int cube_score;														//Stores the score associated with the cube
	CScore m_score;														//Allows access to the score in the score class
	CAudio m_audio;
};