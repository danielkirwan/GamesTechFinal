#pragma once
#include <Windows.h>
#include "Vector3f.h"
#include "Camera.h"
#include "Md2Animation.h"
#include "BoundingBox.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include ".\include\glew.h"
#include ".\include\GL.H"
#include "Fireball.h"

#define STAND 0
#define RUN 1
#define ATTACK 2


class CXenoid
{
public:
	CXenoid();									//Constructor
	~CXenoid();									//Destructor
	void Update(float dt,CVector3f playerPos);	//Update object
	void Initialise(CVector3f p);				//Initialise object
	void Render();								//Render object
	bool m_isActive;							//Is active
	CVector3f GetPosition() const;				//get theplayer position in world coordinates???
	void Turn(float angle);						//Turn the player left/right
	CVector3f m_position;						//Position of player
	void Attack();								//Attack method for animation
	void Advance(float speed);					//Move player forward
	void SetSpeed(float speed);					//Set player speed
	void Stand();								//Stand animation
	void SetPosition(CVector3f setPos);			//Set position
	CBoundingBox GetBBox();						//Return bounding box
	CFireball m_fireball;						//Fireball object, was intending for the eXenoid class to throw a fireball when the player gets close enough
	Camera m_camera;							//Camera object, in use with above
	int health;									//Xenoid health
private:

	CVector3f m_direction;						//Direction they are facing
	float m_speed;								//Player speed
	CMD2Model m_mesh;							//Player mesh model
	CBoundingBox m_bbox;						//Bounding box
};

