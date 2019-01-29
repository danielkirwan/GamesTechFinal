#pragma once

#include <Windows.h>
#include "Vector3f.h"
#include "Camera.h"
#include "Md2Animation.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include ".\include\glew.h"
#include ".\include\GL.H"
#include"BoundingBox.h"
#define STAND 0
#define RUN 1
#define ATTACK 2

class CBobbafett
{
public:
	CBobbafett();
	~CBobbafett();

	void Update(float dt, CVector3f playerPos);	//Update the object
	void Initialise(CVector3f p);				//Initialise the object
	void Render();								//Render the object
	CVector3f GetPosition() const;				//Return Position
	CVector3f m_position;						//Position of player
	CBoundingBox m_bbox;						//Bounding box
	void Attack();								//Attack method for animation
	void Advance(float speed);					//Move player forward
	void SetSpeed(float speed);					//Set player speed
	void Stand();								//Change animation
	int health;									//Object health
	bool m_isActive;							//Is active??
	CBoundingBox GetBBox();						//return the bounding box
	bool IsActive(bool);						//Un used method		
private:
	CVector3f m_direction;						//Direction they are facing
	float m_speed;								//Player speed

	CMD2Model m_mesh;							//Mesh for the object

};