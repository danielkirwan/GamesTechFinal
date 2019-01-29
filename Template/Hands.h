#pragma once
#include "OpenAssetimporterMesh.h"
#include "Vector3f.h"


class CHands
{
public:
	CHands();
	~CHands();
	COpenAssetImporterMesh m_mesh;	
	CVector3f m_position;
	GLfloat position;
	void Initialise(CVector3f pos);
	void Render();
};

