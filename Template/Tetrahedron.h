#pragma once
#include <Windows.h>

class CTetrahedron 
{
public:
	CTetrahedron();										//Constructor
	~CTetrahedron();									//Destructor
	void Initialise();									//Initialise object
	void Render(float r, float g, float b, float a);	//Render object

private: 
	UINT m_textureID;									//Texture IDs
};
