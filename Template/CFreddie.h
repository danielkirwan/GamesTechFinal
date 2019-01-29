#pragma once
#include <Windows.h>
#include "Vector3f.h"
#include "BoundingBox.h"
#include "OpenAssetImporterMesh.h"
#include ".\include\glew.h"
#include ".\include\GL.H"
#include "Texture.h"
class CFreddie
{
public:
	CFreddie();										//Constructor
	~CFreddie();									//Destructor
	void Initialise(CVector3f p);					//Initialise the object
	CBoundingBox GetBBox();							//Return bounding box
	CBoundingBox m_bbox;							//Bounding box
	CVector3f GetPosition() const;					//Return object position
	void Update(float dt, CVector3f playerPos);		//Update the object
	bool m_isActive;								//Is object active
	void Render();									//Render object
private:
	COpenAssetImporterMesh m_mesh;					//Mesh for object
	CVector3f m_position;							//Player position
};

