#include "Score.h"
#include "Cube.h"
#include <string>

CScore::CScore(){}
CScore::~CScore(){}

void CScore::Initialise(int score)
{
	score = score;
}

void CScore::Update(int score)
{
	m_score = score;
}

void CScore::Render()
{
	glDisable(GL_LIGHTING);
	char scoreText[128];
	sprintf_s(scoreText, "Score = %d\n", m_score);
	m_text.Render(scoreText, 10, 540, 1, 0.5, 0);
	glEnable(GL_LIGHTING);
}

