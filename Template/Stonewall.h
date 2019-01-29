#pragma once
#include <Windows.h>
#include "Vector3f.h"
#include "BoundingBox.h"
#include "OpenAssetImporterMesh.h"
#include ".\include\glew.h"
#include ".\include\GL.H"
#include "Texture.h"
class CStonewall
{
public:
	CStonewall();					//Constructor
	~CStonewall();					//Destructor
	void Initialise(CVector3f p);	//Initialise object
	CBoundingBox GetBBox();			//Return bounding box
	CVector3f GetPosition() const;	//Return position
	CBoundingBox m_bbox;			//Bounding box
	void Render();					//Render Object
private:
	COpenAssetImporterMesh m_mesh;	//Mesh for object
	CVector3f m_position;			//Position
};

