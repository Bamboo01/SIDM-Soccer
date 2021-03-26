#include "FootballPlayer.h"

void FootballPlayer::Init(GameObject* paddleL, GameObject* paddleR, GameObject* center, GameObject* goalie)
{
	this->paddleL = paddleL;
	this->paddleR = paddleR;
	this->center = center;
	this->goalie = goalie;

	center->type = GameObject::GO_PILLAR;
	center->active = true;
	center->pos = Vector3(20, 20, 0);
	center->scale = Vector3(2, 2, 1);
	center->rot = Vector3(0, 0, 0);
	center->color = Vector3(1, 0, 0);
	center->mass = 3.f;
	center->momentumCoefficient = 0.8f;

	paddleL->type = GameObject::GO_MOVING_WALL;
	paddleL->center = Vector3(7.5, 0, 0);
	paddleL->active = true;
	paddleL->pos = Vector3(0, 0, 0);
	paddleL->parent = center;
	paddleL->scale = Vector3(10, 2, 1);
	paddleL->rot = Vector3(0, 0, 0);
	paddleL->color = Vector3(1, 0, 0);
	paddleL->mass = 3.f;
	paddleL->momentumCoefficient = 0.8f;

	paddleR->type = GameObject::GO_MOVING_WALL;
	paddleR->center = Vector3(-7.5, 0, 0);
	paddleR->active = true;
	paddleR->pos = Vector3(0, 0, 0);
	paddleR->parent = center;
	paddleR->scale = Vector3(10, 2, 1);
	paddleR->rot = Vector3(0, 0, 0);
	paddleR->color = Vector3(1, 0, 0);
	paddleR->mass = 3.f;
	paddleR->momentumCoefficient = 0.8f;

	goalie->type = GameObject::GO_MOVING_WALL;
	goalie->center = Vector3(-7.5, 0, 0);
	goalie->active = true;
	goalie->pos = Vector3(0, 0, 0);
	goalie->scale = Vector3(30, 2, 1);
	goalie->rot = Vector3(0, 0, 0);
	goalie->color = Vector3(1, 0, 0);
	goalie->mass = 1.f;
	goalie->momentumCoefficient = 0.6f;
}

void FootballPlayer::Update()
{
	if (paddleL->rot.z >= 60)
	{
		paddleL->rot.z = 60;
	}

	if (paddleR->rot.z <= -60)
	{
		paddleR->rot.z = -60;
	}
}

void FootballPlayer::MoveForward()
{
	center->vel = center->axisY * 25.f;
}

void FootballPlayer::MoveBackwards()
{
	center->vel = center->axisY * -15.f;
}

void FootballPlayer::StrafeLeft()
{
	center->vel = center->axisX * -20.f;
}

void FootballPlayer::StrafeRight()
{
	center->vel = center->axisX * 20.f;
}

void FootballPlayer::RotateLeft()
{
	center->angularVelocity.Set(0, 0, 90);
}

void FootballPlayer::RotateRight()
{
	center->angularVelocity.Set(0, 0, -90);
}

void FootballPlayer::StopMoving()
{
	center->vel.SetZero();
}

void FootballPlayer::StopRotating()
{
	center->angularVelocity.SetZero();
}

void FootballPlayer::KickLeft()
{
	paddleL->angularVelocity = Vector3(0, 0, 180);
}

void FootballPlayer::StopKickingLeft()
{
	paddleL->angularVelocity.SetZero();
	if (paddleL->rot.z > 0)
	{
		paddleL->angularVelocity = Vector3(0, 0, -180);
	}
	else if (paddleL->rot.z <= 0)
	{
		if (paddleL->rot.z <= 0)
		{
			paddleL->rot.z = 0;
		}
	}
}

void FootballPlayer::KickRight()
{
		paddleR->angularVelocity = Vector3(0, 0, -180);
}


void FootballPlayer::StopKickingRight()
{
	if (paddleR->rot.z < 0)
	{
		paddleR->angularVelocity = Vector3(0, 0, 180);
	}
	else
	{
		paddleR->angularVelocity.SetZero();
		if (paddleR->rot.z >= 0)
		{
			paddleR->rot.z = 0;
		}
	}
}

void FootballPlayer::RotateGoalieLeft()
{
	goalie->angularVelocity.Set(0, 0, 180);
}

void FootballPlayer::RotateGoalieRight()
{
	goalie->angularVelocity.Set(0, 0, -180);
}

void FootballPlayer::StopGoalie()
{
	goalie->angularVelocity.SetZero();
}

