#include "CameraFP.h"
#include <Windows.h>

#include ".\include\glew.h"									// Header File For The Glaux Library
#include ".\include\Gl.H"											// Header File For The OpenGL32 Library
#include ".\include\glu.h"									// Header File For The GLu32 Library

#include <math.h>

#include "gamewindow.h"


CameraFP::CameraFP()
{
	m_position = CVector3f(0.0f, 4.0f, 0.0f);
	m_viewPoint = CVector3f(0.0f, 1.0f, 5.0f);
	m_upVector = CVector3f(0.0f, 1.0f, 0.0f);
	m_speed = 5.0f;
	m_totalVerticalRotation = 0.0f;
}

void CameraFP::Set(const CVector3f & position, const CVector3f & view, const CVector3f & up_vector, const float & speed)
{
	m_position = position;
	m_viewPoint = view;
	m_upVector = up_vector;
	m_speed = speed;

	Look();
}

CVector3f CameraFP::GetPosition() const
{
	return m_position;
}

CVector3f CameraFP::GetViewPoint() const
{
	return m_viewPoint;
}

CVector3f CameraFP::GetUpVector() const
{
	return m_upVector;
}

CVector3f CameraFP::GetStrafeVector() const
{
	return m_strafeVector;
}

void CameraFP::Strafe(float speed)
{
	m_position.x += m_strafeVector.x * speed;
	m_position.z += m_strafeVector.z * speed;

	m_viewPoint.x += m_strafeVector.x * speed;
	m_viewPoint.z += m_strafeVector.z * speed;
}

void CameraFP::Advance(float speed)
{
	CVector3f view = m_viewPoint - m_position;
	view.Normalise();

	m_position += view * speed;
	m_viewPoint += view * speed;
}

void CameraFP::MoveUp(float speed)
{
	m_position += m_upVector * speed;
	m_viewPoint += m_upVector * speed;
}

void CameraFP::Update(double dt)
{
	Movement(dt);
	SetViewByMouse();
}

void CameraFP::Look()
{
	gluLookAt(
		m_position.x, m_position.y, m_position.z,
		m_viewPoint.x, m_viewPoint.y, m_viewPoint.z,
		m_upVector.x, m_upVector.y, m_upVector.z);

	m_strafeVector = (m_viewPoint - m_position) % m_upVector;
	m_strafeVector.Normalise();
}

void CameraFP::RotateView(float angle, CVector3f &vector)
{
	CVector3f view = m_viewPoint - m_position;
	CVector3f rotatedView = view.RotateAboutAxis(angle, vector);
	m_viewPoint = m_position + rotatedView;
}

void CameraFP::SetViewByMouse()
{
	int middle_x = GameWindow::SCREEN_WIDTH >> 1;
	int middle_y = GameWindow::SCREEN_HEIGHT >> 1;


	POINT mouse;
	GetCursorPos(&mouse);

	if (mouse.x == middle_x && mouse.y == middle_y) {
		return;
	}

	SetCursorPos(middle_x, middle_y);

	float dx = (float)(middle_x - mouse.x) / 50.0f;
	float dy = (float)(middle_y - mouse.y) / 50.0f;


	m_totalVerticalRotation += dy;

	// Clip the rotation rotation about the strafe vector to [-MAX_STRAFE_ROTATION, MAX_STRAFE_ROTATION]
	if (m_totalVerticalRotation > MAX_VERTICAL_ROTATION) {
		m_totalVerticalRotation = MAX_VERTICAL_ROTATION;
	}
	else if (m_totalVerticalRotation < -MAX_VERTICAL_ROTATION) {
		m_totalVerticalRotation = -MAX_VERTICAL_ROTATION;
	}
	else {
		RotateView(dy, m_strafeVector);
	}

	RotateView(dx, CVector3f(0, 1, 0));
}

void CameraFP::Movement(double dt)
{
	float speed = (float)dt * m_speed;

	if ((GetKeyState(VK_UP) & 0x80 || GetKeyState('W') & 0x80)) {
		Advance(speed);	// Forward
	}

	if ((GetKeyState(VK_DOWN) & 0x80 || GetKeyState('S') & 0x80)) {
		Advance(-speed);	// Backward
	}

	if ((GetKeyState(VK_LEFT) & 0x80 || GetKeyState('A') & 0x80)) {
		Strafe(-speed); // Left
	}

	if ((GetKeyState(VK_RIGHT) & 0x80 || GetKeyState('D') & 0x80)) {
		Strafe(speed); // Right
	}
}


