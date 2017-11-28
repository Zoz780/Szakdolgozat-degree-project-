#pragma once
#include "VboDrawer.h"
#include <assert.h>

#define _USE_MATH_DEFINES
#include <math.h>

class Character
{
public:
	Character();
	//Értékek beállítása, visszaadása---------------------------------------------
	void SetXpos(float x);
	float GetXpos();
	void SetYpos(float y);
	float GetYpos();
	void Turn(float angle);
	float GetTurn();

	//-----------------------------------------------------------------------------

	/**
			*Karakter animációja
	*/
	void Animate(double dt);

	/**
			*Adott rész kirajzolása
	*/
	void DrawLeftArm(float xPos, float yPos, float zPos, float angle);

	/**
			*Adott rész kirajzolása
	*/
	void DrawRightArm(float xPos, float yPos, float zPos, float angle);

	/**
			*Adott rész kirajzolása
	*/
	void DrawLeftLeg(float xPos, float yPos, float zPos, float angle);

	/**
			*Adott rész kirajzolása
	*/
	void DrawRightLeg(float xPos, float yPos, float zPos, float angle);

	/**
			*Robot részeinek betöltése (VBO)
	*/
	void Load();

	/**
			*Robot felépítése a betöltött modellekbõl
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

