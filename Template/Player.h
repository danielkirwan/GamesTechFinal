#pragma once

#include <Windows.h>
#include "Vector3f.h"
#include "Camera.h"
#include "Md2Animation.h"
#include "BoundingBox.h"
#include <math.h>
#include ".\include\glew.h"
#include ".\include\GL.H"
#define _USE_MATH_DEFINES

#define YOHKO_RUN 1
#define YOHKO_ATTACK 2
#define YOHKO_STAND 0



class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void Update(float dt);
	void Initialise();
	void Render();

	void UpdateCamera(Camera &camera, double dt);		//Update camera based on player
	CVector3f GetPosition() const;			//get theplayer position in world coordinates???
	void Turn(float angle);					//Turn the player left/right
	void Attack();							//Attack method for animation
	CVector3f m_position;					//Position of player
	void Advance(float speed);				//Move player forward
	void SetSpeed(float speed);				//Set player speed
	void Strafe(float speed);				//Move player sideways
	void Movement(double dt);
	void Stand();
	void SetPosition(CVector3f setPos);
	CBoundingBox GetBBox();
	
private:
	
	CVector3f m_direction;					//Direction they are facing
	float m_speed;							//Player speed
	CVector3f m_upVector;					//Player upVector
	CVector3f m_strafeVector;				//Player Strafe vector
	CMD2Model m_mesh;						//Player mesh model
	CBoundingBox m_bbox;
	Camera m_camera;
};
