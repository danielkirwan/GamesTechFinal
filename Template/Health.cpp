#include "Health.h"



CHealth::CHealth()
{
}


CHealth::~CHealth()
{
}

void CHealth::Initialise(int health)
{
	m_health = health;
}

void CHealth::Update(int health)
{
	m_health = health;
}

void CHealth::Render()
{
}
