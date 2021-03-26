#include "PlayerController.h"
#include "Application.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::Init(FootballPlayer* fbp)
{
	this->fbp = fbp;
}

void PlayerController::Update(float dt, GameObject* ball)
{
	Vector3 ballpos = ball->pos;

	if (Application::IsKeyPressed('W'))
	{
		fbp->MoveForward();
	}
	else if (Application::IsKeyPressed('Q'))
	{
		fbp->StrafeLeft();
	}
	else if (Application::IsKeyPressed('E'))
	{
		fbp->StrafeRight();
	}
	else if (Application::IsKeyPressed('S'))
	{
		fbp->MoveBackwards();
	}
	else
	{
		fbp->StopMoving();
	}

	if (Application::IsKeyPressed('D'))
	{
		fbp->RotateRight();
	}
	else if (Application::IsKeyPressed('A'))
	{
		fbp->RotateLeft();
	}
	else
	{
		fbp->StopRotating();
	}

	if (Application::IsKeyPressed('G'))
	{
		fbp->KickLeft();
	}
	else
	{
		fbp->StopKickingLeft();
	}

	if (Application::IsKeyPressed('F'))
	{
		fbp->KickRight();
	}
	else
	{
		fbp->StopKickingRight();
	}

	Vector3 pospos =  ballpos - fbp->goalie->pos;
	float goalie2ball = Math::RadianToDegree(atan2f(pospos.y, pospos.x));
	goalie2ball -= fbp->goalie->rot.z + 90.f;

	if (Math::FAbs(goalie2ball) > 8.f && pospos.Length() < 80.f)
	{
		if (goalie2ball < 0)
		{
			if (pospos.Length() < 25.f)
				fbp->RotateGoalieLeft();
			else
			fbp->RotateGoalieRight();
		}
		else
		{
			if (pospos.Length() < 25.f)
				fbp->RotateGoalieRight();
			else
				fbp->RotateGoalieLeft();
		}
	}
	else
	{
		fbp->StopGoalie();
	}

	fbp->Update();
}
