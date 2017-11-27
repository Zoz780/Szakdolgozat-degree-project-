#pragma once
class Action
{
public:
	Action();

	//go Forward
	void startGoForward();
	void stopForward();
	bool needGoForward() const;

	//go Backward
	void startGoBackward();
	void stopBackward();
	bool needGoBackward() const;

	//Turn left
	void startTurnLeft();
	void stopTurnLeft();
	bool needTurnLeft() const;

	//Turn right
	void startTurnRight();
	void stopTurnRight();
	bool needTurnRight() const;

	//Change Camera View
	void changeCameraView();
	bool getCameraView() const;

	//Go Up
	void startGoUp();
	void stopGoUp();
	bool needGoUp() const;

	//Go Down
	void startGoDown();
	void stopGoDown();
	bool needGoDown() const;

private:
	bool m_isGoForward;
	bool m_isGoBackward;
	bool m_isTurnLeft;
	bool m_isTurnRight;
	bool m_camIsFree;
	bool m_isGoUp;
	bool m_isGoDown;
};

