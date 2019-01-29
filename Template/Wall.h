#pragma once

#include <Windows.h>
#include "Vector3f.h"
#include "BoundingBox.h"
#include "OpenAssetImporterMesh.h"
#include ".\include\glew.h"
#include ".\include\GL.H"
#include "Texture.h"


class CWall
{
public:
	CWall();							//Constructor
	~CWall();							//Destructor
	void Initialise(CVector3f p);		//Initialise object
	void Render();						//Render object
	void RenderSide();					//Render Side
	void RenderXWall();					//RenderXWall
	void RenderYWall();					//RenderYWall
	void SetPosition(CVector3f setPos);	//SetPosition
	CBoundingBox GetBBox();				//Return bounding box
	CVector3f GetPosition() const;		//Return position
	CBoundingBox m_bbox;				//Bounding box
	void Update();						//Update object


private:
	UINT m_textureID;					//Texture ID
	COpenAssetImporterMesh m_mesh;		//Mesh object
	CVector3f m_position;				//Position
};

