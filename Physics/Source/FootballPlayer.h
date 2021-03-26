#include "GameObject.h"

#pragma once
class FootballPlayer
{
public:
	GameObject* paddleL;
	GameObject* paddleR;
	GameObject* center;
	GameObject* goalie;


	FootballPlayer() {}

	~FootballPlayer() {}

	void Init(GameObject* paddleL, GameObject* paddleR, GameObject* center, GameObject* goalie);

	void Update();

	void MoveForward();

	void MoveBackwards();

	void StrafeLeft();

	void StrafeRight();

	void RotateLeft();

	void RotateRight();

	void StopMoving();
	
	void StopRotating();

	void KickLeft();

	void StopKickingLeft();

	void KickRight();

	void StopKickingRight();

	void RotateGoalieLeft();

	void RotateGoalieRight();

	void StopGoalie();
};

