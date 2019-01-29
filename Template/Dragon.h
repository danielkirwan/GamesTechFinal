#pragma once
#include <Windows.h>
#include "Vector3f.h"
#include "BoundingBox.h"
#include "OpenAssetImporterMesh.h"
#include ".\include\glew.h"
#include ".\include\GL.H"
#include "Texture.h"
class CDragon
{
public:
	CDragon();							//Constructor
	~CDragon();							//Destructor
	void Initialise(CVector3f p);		//initialise object
	CBoundingBox GetBBox();				//Return bounding box
	CVector3f GetPosition() const;		//Return position
	CBoundingBox m_bbox;				//Mesh object
	void Render();						//Render object
	bool m_isActive;					//Is active
private:
	COpenAssetImporterMesh m_mesh;		//Mesh for object
	CVector3f m_position;				//Position
};

