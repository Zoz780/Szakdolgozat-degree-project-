#include "Character.h"

Character::Character()
{
	leftarm_angle = 180; rightarm_angle = 180;
	leftleg_angle = 180; rightleg_angle = 180;
	dleftarm_angle = 30;  drightarm_angle = -30;
	dleftleg_angle = -30; drightleg_angle = 30;
	forward = 0, side = 0;
	zrot = 0;
	xpos = 0, ypos = 0;
}

void Character::Load()
{
	head.Load("Models/head.obj", 2.0f, 2.0f, 2.0f, "Textures/head.png");
	torso.Load("Models/torso.obj", 2.0f, 2.0f, 2.0f, "Textures/torso.png");
	left_arm.Load("Models/left_arm.obj", 2.0f, 2.0f, 2.0f, "Textures/texture.png");
	right_arm.Load("Models/right_arm.obj", 2.0f, 2.0f, 2.0f, "Textures/texture.png");
	left_leg.Load("Models/left_leg.obj", 2.0f, 2.0f, 2.0f, "Textures/texture.png");
	right_leg.Load("Models/right_leg.obj", 2.0f, 2.0f, 2.0f, "Textures/texture.png");
}

void Character::Animate(double dt) { 
	oldleg_angle = rightleg_angle;  
	leftarm_angle += dleftarm_angle * dt * 4;
	rightarm_angle += drightarm_angle * dt * 4;
	leftleg_angle += dleftleg_angle * dt * 4;
	rightleg_angle += drightleg_angle * dt * 4;

	if (leftarm_angle > 210) { dleftarm_angle = -30; drightarm_angle = 30; }
	if (rightarm_angle > 210) { dleftarm_angle = 30; drightarm_angle = -30; }
	if (leftleg_angle < 150) { dleftleg_angle = 30; drightleg_angle = -30; }
	if (rightleg_angle < 150) { dleftleg_angle = -30; drightleg_angle = 30; }

	forward += fabs(5 * (sin((rightleg_angle - 180) * M_PI / 180) - sin((oldleg_angle - 180) * M_PI / 180)));
	up = (float)(5.0 * cos((rightleg_angle - 180) * M_PI / 180) - 5.0);
}

void Character::SetXpos(float x) { xpos = x; }
float Character::GetXpos() { return xpos; }
void Character::SetYpos(float y) { ypos = y; }
float Character::GetYpos() { return ypos; }
void Character::Turn(float angle) { zrot = angle; }
float Character::GetTurn() { return zrot; }

void Character::DrawLeftArm(float xPos, float yPos, float zPos, float angle) 
{
	glPushMatrix();
	glColor4f(0.8f, 0.8f, 1.0f, 1.0f);
	glTranslatef(xPos, yPos, zPos); 
	glRotatef(angle, 0, 1, 0);      
	left_arm.DrawModel(0, 0, 0);
	glPopMatrix();                  
}
void Character::DrawRightArm(float xPos, float yPos, float zPos, float angle) 
{
	glPushMatrix();                
	glTranslatef(xPos, yPos, zPos); 
	glRotatef(angle, 0, 1, 0);      
	right_arm.DrawModel(0, 0, 0);
	glPopMatrix();                  
}
void Character::DrawLeftLeg(float xPos, float yPos, float zPos, float angle) 
{
	glPushMatrix();
	glTranslatef(xPos, yPos, zPos); 
	glRotatef(angle, 0, 1, 0);      
	left_leg.DrawModel(0, 0, 0);
	glPopMatrix();                  
}

void Character::DrawRightLeg(float xPos, float yPos, float zPos, float angle)
{
	glPushMatrix();                 
	glTranslatef(xPos, yPos, zPos); 
	glRotatef(angle, 0, 1, 0);      
	right_leg.DrawModel(0, 0, 0);
	glPopMatrix();                  
}
void Character::Draw() 
{
	glPushMatrix();
	glTranslatef(xpos, ypos, up);
	glRotatef(zrot, 0, 0, 1);
	head.DrawModel(0, 0, 22);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	torso.DrawModel(0, 0, 13.5);
	DrawLeftArm(0, 3.05, 20.5, leftarm_angle);
	DrawRightArm(0, -3.05, 20.5, rightarm_angle);
	DrawLeftLeg(0.6, 0.9, 14, leftleg_angle);
	DrawRightLeg(0.6, -0.9, 14.3, rightleg_angle); 
	glPopMatrix();
}


