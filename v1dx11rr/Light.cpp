#include "Light.h"

Light::Light()
{

	m_direction[0] = 0.5f;
	m_direction[1] = -1.0f;
	m_direction[2] = 0.0f;

	m_diffuseColor[0] = 0.2f;
	m_diffuseColor[1] = 0.2f;
	m_diffuseColor[2] = 1.0f;
	m_diffuseColor[3] = 1.0f;
}


Light::Light(const Light& other)
{
}

Light::Light(float posx, float posy, float posz, float r, float g, float b, float a) {

	m_direction[0] = posx;
	m_direction[1] = posy;
	m_direction[2] = posz;

	m_diffuseColor[0] = r;
	m_diffuseColor[1] = g;
	m_diffuseColor[2] = b;
	m_diffuseColor[3] = a;
}

Light::~Light()
{
}


void Light::SetDiffuseColor(float alpha, float red, float green, float blue)
{
	m_diffuseColor[0] = alpha;
	m_diffuseColor[1] = red;
	m_diffuseColor[2] = green;
	m_diffuseColor[3] = blue;
	return;
}


void Light::SetDirection(float x, float y, float z)
{
	m_direction[0] = x;
	m_direction[1] = y;
	m_direction[2] = z;
	return;
}


void Light::GetDiffuseColor(float* color)
{
	color[0] = m_diffuseColor[0];
	color[1] = m_diffuseColor[1];
	color[2] = m_diffuseColor[2];
	color[3] = m_diffuseColor[3];
	return;
}


void Light::GetDirection(float* direction)
{
	direction[0] = m_direction[0];
	direction[1] = m_direction[1];
	direction[2] = m_direction[2];
	return;
}

float* Light::GetDiffuseColor()
{
	return this->m_diffuseColor;
}


float* Light::GetDirection()
{
	return this->m_direction;
}
