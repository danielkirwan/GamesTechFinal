#include "Fireball.h"



CFireball::CFireball()
{
	// Initialise static physical quantities
	m_radius = 0.22f; // in meters
	m_mass = 0.45f; // in kg
	m_rotationalInertia = (2.0f / 3.0f) * m_mass * m_radius * m_radius; // in kg m^2
	m_coefficientOfRestitution = 0.85f; // percentage
	m_contactTime = 0.05f; // in seconds
	m_bbox.SetSize(0.5f,0.5f,0.5f);
	m_bbox.SetBottom(m_position);
	damage = 1;
	m_isActive = true;
}


CFireball::~CFireball()
{
	this->m_isActive = false;
}

void CFireball::Throw(Camera camera)
{
	CVector3f cameraPos = camera.GetPosition();
	CVector3f viewPoint = camera.GetViewPoint();
	CVector3f direction = viewPoint - cameraPos;	// Direction camera is facing
	direction.Normalise();							// Normalised direction camera is facing.  We'll launch the ball in this direction

	// Initialise all physical variables
	m_position = CVector3f(0.0f, 0.0f, 0.0f);
	//m_velocity = CVector3f(0.0f, 0.0f, 0.0f);
	//m_acceleration = CVector3f(0.0f, 0.0f, 0.0f);
	m_acceleration = CVector3f(0.0f, -9.8f, 0.0f);
	m_instantaneousAcceleration = CVector3f(0.0f, 0.0f, 0.0f);
	m_angle = CVector3f(0.0f, 0.0f, 0.0f);
	m_angularVelocity = CVector3f(0.0f, 0.0f, 0.0f);
	m_angularAcceleration = CVector3f(0.0f, 0.0f, 0.0f);
	m_instantaneousAngularAcceleration = CVector3f(0.0f, 0.0f, 0.0f);
	m_contactTime = 0.0f;


	// Set the ball to the current camera position
	m_position = camera.GetPosition();
	m_velocity = 25.0f * direction;


	// Determine rotation angles of camera (from Lab 4)
	m_theta = 90.0f - (180.0f / 3.141529f) * acos(direction.y);
	m_phi = (180.0f / 3.1415290f) * atan2(direction.x, direction.z);

	CVector3f m_force = direction;
	m_force.Normalise();
	m_force = m_force * 270;
	m_instantaneousAcceleration = m_force / m_mass;

	CVector3f m_torque = CVector3f(1, 0, 0);
	m_torque.Normalise();
	m_torque = m_torque * 200;
	m_instantaneousAngularAcceleration = m_torque / m_rotationalInertia;

	m_bbox.SetBottom(CVector3f(m_position.x, m_position.z -0.5f, m_position.z));
}


void CFireball::Update(float dt)
{
	// Update physical quanitities
	m_lastPosition = m_position;
	m_position += m_velocity * dt;
	m_angle += m_angularVelocity * dt;
	m_angularVelocity += (m_angularAcceleration + m_instantaneousAngularAcceleration) * dt;
	//Slide 33 week 7 section 6.Lab session
	m_velocity += (m_acceleration + m_instantaneousAcceleration)* dt;

	// Turn off instantaneous forces if contact time is surpassed
	if (m_instantaneousAcceleration.Length() > 0 && m_contactTime > 0.05) {
		m_instantaneousAcceleration = CVector3f(0, 0, 0);
		m_instantaneousAngularAcceleration = CVector3f(0, 0, 0);
		m_contactTime = 0;
	}
	m_contactTime += dt;

	// Check for collision detection
	float yPlane = 0.0f;
	if (CollisionDetection(yPlane)) {
		CollisionResponse();
	}

	m_bbox.SetBottom(m_position);

}

void CFireball::Initialise(char * filename)
{
	m_mesh.Load(filename);
	m_bbox.SetSize(0.5f, 0.5f, 0.5f);
	m_bbox.SetBottom(m_position);
}

void CFireball::Render()
{
	if(m_isActive)
	{
		glPushMatrix();
	glTranslatef(m_position.x, m_position.y, m_position.z);

	glRotatef(m_phi, 0, 1, 0);
	glRotatef(-m_theta, 1, 0, 0);
	if (m_angle.Length() > 0)
		glRotatef(m_angle.Length(), m_angle.x, m_angle.y, m_angle.z);	// Rotate the ball resulting from torque

	m_mesh.Render();
	glPopMatrix();
	}
#if(_DEBUG)
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	m_bbox.Render(1, 0, 0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

#endif

}



CVector3f CFireball::GetPosition()
{
	return m_position;
}

CVector3f CFireball::GetLastPosition()
{
	return m_lastPosition;
}

bool CFireball::CollisionDetection(float yPlane)
{
	// Check for collision with the ground by looking at the y value of the ball's position
	if (m_position.y - m_radius < yPlane && m_velocity.y < 0) {
		return true;
	}
	return false;
}

bool CFireball::IsActive()
{
	m_isActive = false;
	return m_isActive;
}

void CFireball::CollisionResponse()
{
	float convergenceThreshold = 0.5f;
	if (m_velocity.Length() > convergenceThreshold) {
		m_coefficientOfRestitution = 0.70f;
		// The ball has bounced!  Implement a bounce by flipping the y velocity.
		m_velocity = CVector3f(m_velocity.x, -m_velocity.y, m_velocity.z) * m_coefficientOfRestitution;

	}
	else {
		// Velocity of the ball is below a threshold.  Stop the ball. 
		m_velocity = CVector3f(0.0f, 0.0f, 0.0f);
		m_acceleration = CVector3f(0.0f, 0.0f, 0.0f);
		m_position = CVector3f(m_position.x, m_radius, m_position.z);
		m_angularVelocity = CVector3f(0.0f, 0.0f, 0.0f);
	}
}

CBoundingBox CFireball::GetBBox()
{
	return m_bbox;
}
