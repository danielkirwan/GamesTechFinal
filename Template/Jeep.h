#pragma once
#include <Windows.h>
#include "Vector3f.h"
#include "BoundingBox.h"
#include "OpenAssetImporterMesh.h"
#include ".\include\glew.h"
#include ".\include\GL.H"
#include "Texture.h"
class CJeep
{
public:
	CJeep();						//Contrustor
	~CJeep();						//Destructor
	void Initialise(CVector3f p);	//Initialise object
	CBoundingBox GetBBox();			//Return bounding box
	CVector3f GetPosition() const;	//Return psoition
	CBoundingBox m_bbox;			//Mesh for object
	void Render();					//Render object
private:
	COpenAssetImporterMesh m_mesh;	//Mesh for object
	CVector3f m_position;			//Position of object
};

