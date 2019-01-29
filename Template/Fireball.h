#pragma once
#include <windows.h>									
#include "Vector3f.h"
#include "Camera.h"
#include "OpenAssetimporterMesh.h"
#include "BoundingBox.h"

class CFireball
{
public:
	CFireball();
	~CFireball();
	void Throw(Camera camera);
	void Update(float dt);
	void Initialise(char *filename);
	void Render();
	CVector3f GetPosition();
	CVector3f GetLastPosition();
public:

	// Linear physical quantities
	CVector3f m_position;
	CVector3f m_velocity;
	CVector3f m_acceleration;
	CVector3f m_instantaneousAcceleration;
	CVector3f m_lastPosition;

	// Rotational physical quantities
	CVector3f m_angle;
	CVector3f m_angularVelocity;
	CVector3f m_angularAcceleration;
	CVector3f m_instantaneousAngularAcceleration;


	// Other physical quantities
	float m_mass; // in kg
	float m_rotationalInertia; // in kg m^2
	float m_contactTime; // in seconds
	float m_coefficientOfRestitution; // as a percentage
	float m_radius; // radius of ball in meters

	// Angles used for rendering (see Lab 4)
	float m_theta;
	float m_phi;

	// Mesh
	COpenAssetImporterMesh m_mesh;

	// Methods to handle collisions with the ground
	bool CollisionDetection(float yPlane);
	bool IsActive();
	void CollisionResponse();
	CBoundingBox GetBBox();
	CBoundingBox m_bbox;
	int damage;
	bool m_isActive;
};

