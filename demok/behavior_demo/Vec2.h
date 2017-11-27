#pragma once
#include <math.h>
class Vec2
{
public:
	Vec2();

	void SetX(float x);
	float GetX();

	void SetY(float y);
	float GetY();


	float GetLength() const;

	void Normalize();

	void SetMagnitude(float magnitude);

private:
	float m_x;
	float m_y;
};