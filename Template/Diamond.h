#pragma once
#include <Windows.h>

class CDiamond
{
public:
	CDiamond();
	~CDiamond();
	void Initialise();
	void Render(float r, float g, float b, float a);

private:
	UINT m_textureID;
};

