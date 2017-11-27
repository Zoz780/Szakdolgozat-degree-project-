#include "Vec2.h"



Vec2::Vec2()
{
	m_x = 0.0f;
	m_y = 0.0f;
}


void Vec2::SetX(float x)
{
	m_x = x;
}

float Vec2::GetX()
{
	return m_x;
}

void Vec2::SetY(float y)
{
	m_y = y;
}

float Vec2::GetY()
{
	return m_y;
}

float Vec2::GetLength() const
{
	return sqrtf(m_x*m_x + m_y*m_y);
}

void Vec2::Normalize()
{
	float magnitude = GetLength();
	if (magnitude == 0.0)
		magnitude = 0.000001f;
	magnitude = 1 / magnitude;
	m_x *= magnitude;
	m_y *= magnitude;
}

void Vec2::SetMagnitude(float magnitude)
{
	Normalize();
	m_x *= magnitude;
	m_y *= magnitude;
}
