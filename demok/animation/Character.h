#pragma once
#include "VboDrawer.h"
#include <assert.h>

#define _USE_MATH_DEFINES
#include <math.h>

class Character
{
public:
	Character();
	//�rt�kek be�ll�t�sa, visszaad�sa---------------------------------------------
	void SetXpos(float x);
	float GetXpos();
	void SetYpos(float y);
	float GetYpos();
	void Turn(float angle);
	float GetTurn();

	//-----------------------------------------------------------------------------

	/**
			*Karakter anim�ci�ja
	*/
	void Animate(double dt);

	/**
			*Adott r�sz kirajzol�sa
	*/
	void DrawLeftArm(float xPos, float yPos, float zPos, float angle);

	/**
			*Adott r�sz kirajzol�sa
	*/
	void DrawRightArm(float xPos, float yPos, float zPos, float angle);

	/**
			*Adott r�sz kirajzol�sa
	*/
	void DrawLeftLeg(float xPos, float yPos, float zPos, float angle);

	/**
			*Adott r�sz kirajzol�sa
	*/
	void DrawRightLeg(float xPos, float yPos, float zPos, float angle);

	/**
			*Robot r�szeinek bet�lt�se (VBO)
	*/
	void Load();

	/**
			*Robot fel�p�t�se a bet�lt�tt modellekb�l
	*/
	void BuildParts();

private:
	float leftarm_angle, rightarm_angle, leftleg_angle, rightleg_angle;
	float dleftarm_angle, drightarm_angle, dleftleg_angle, drightleg_angle;
	float oldleg_angle;  
	float forward, up, side; 
	float xpos, ypos;
	float zrot;
	float distance_v_movement;
	VboDrawer head;
	VboDrawer torso;
	VboDrawer left_arm;
	VboDrawer right_arm;
	VboDrawer left_leg;
	VboDrawer right_leg;
};

