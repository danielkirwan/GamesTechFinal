#pragma once
#include "Vector3f.h"
#include ".\include\glew.h"
#include ".\include\GL.H"
#include <Windows.h>
#include "Score.h"
#include "include/glut.h"
#include "Audio.h"
#include "OpenAssetImporterMesh.h"
#include "BoundingBox.h"
#include "Health.h"

class CMedkit
{
public:
	CMedkit();													//Constructor
	~CMedkit();													//Destructor
	void Initialise(CVector3f pos);								//Initialise object
	void Update(CVector3f c, CHealth *health, float dt, CVector3f medkitPos);	//Update object
	CVector3f GetPosition() const;								//Return position
	void SetPosition(CVector3f setPos);							//Set the position
	void Render();												//Render the object
	CBoundingBox GetBBox();										//Return the bounding box
	CBoundingBox m_bbox;										//Mesh for object
	double m_CubeTheta;											//Amount to rotate
	bool m_isActive;											//Is active
	int healthIncrease;											//health increase
private:
	
	CVector3f m_position;										//Object position
	
	COpenAssetImporterMesh m_mesh;								//Mesh for object
};

