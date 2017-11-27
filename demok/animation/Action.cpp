#include "Action.h"



Action::Action()
{
	m_isGoForward = false;
	m_isGoBackward = false;
	m_isTurnLeft = false;
	m_isTurnRight = false;
	m_camIsFree = false;
	m_isGoUp = false;
	m_isGoDown = false;
}

//Go forward

void Action::startGoForward()
{
	m_isGoForward = true;
}

void Action::stopForward()
{
	m_isGoForward = false;
}

bool Action::needGoForward() const
{
	return m_isGoForward;
}

//Go backward

void Action::startGoBackward()
{
	m_isGoBackward = true;
}

void Action::stopBackward()
{
	m_isGoBackward = false;
}

bool Action::needGoBackward() const
{
	return m_isGoBackward;
}

//Strafe left

void Action::startTurnLeft()
{
	m_isTurnLeft = true;
}

void Action::stopTurnLeft()
{
	m_isTurnLeft = false;
}

bool Action::needTurnLeft() const
{
	return m_isTurnLeft;
}

//Strafe right

void Action::startTurnRight()
{
	m_isTurnRight = true;
}

void Action::stopTurnRight()
{
	m_isTurnRight = false;
}

bool Action::needTurnRight() const
{
	return m_isTurnRight;
}

//Change Camera View

void Action::changeCameraView()
{
	m_camIsFree = !m_camIsFree;
}
bool Action::getCameraView() const
{
	return m_camIsFree;
}

//Go Up
void Action::startGoUp()
{
	m_isGoUp = true;
}
void Action::stopGoUp()
{
	m_isGoUp = false;
}
bool Action::needGoUp() const
{
	return m_isGoUp;
}

//Go Down
void Action::startGoDown()
{
	m_isGoDown = true;
}
void Action::stopGoDown()
{
	m_isGoDown = false;
}
bool Action::needGoDown() const
{
	return m_isGoDown;
}

