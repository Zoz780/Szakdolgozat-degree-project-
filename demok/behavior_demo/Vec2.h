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

	/**
			*T�vols�g kisz�mol�sa
	*/
	float GetLength() const;

	/**
			*�rt�kek normaliz�l�sa
	*/
	void Normalize();

	/**
			*�rt�kek be�ll�t�sa t�vols�g f�ggv�ny�ben
	*/
	void SetMagnitude(float magnitude);

private:
	float m_x;
	float m_y;
};