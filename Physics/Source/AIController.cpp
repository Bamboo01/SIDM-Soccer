#include "AIController.h"

AIController::AIController()
{
}

AIController::~AIController()
{
}

void AIController::Init(FootballPlayer* fbp)
{
	this->fbp = fbp;
}

void AIController::Update(float dt, GameObject* ball)
{
	Vector3 ballpos = ball->pos;
	{
		Vector3 pospos = ballpos - fbp->center->pos;

		float AI2ball = Math::RadianToDegree(atan2f(pospos.y, pospos.x)) - (fbp->center->rot.z) - 90;

		if (Math::FAbs(AI2ball) > 50.f)
		{
			if ((Math::FAbs(AI2ball) > 310.f && Math::FAbs(AI2ball) < 360.f))
			{
				if (AI2ball < 0)
				{
					fbp->RotateLeft();
				}
				else
				{
					fbp->RotateRight();
				}
			}
			else
			{
				if (AI2ball < 0)
				{
					fbp->RotateRight();
				}
				else
				{
					fbp->RotateLeft();
				}
			}
		}
		else
		{
			fbp->StopRotating();
		}

		if (pospos.Length() > 2.f && fabs(AI2ball) < 50.f)
		{
			fbp->MoveForward();
		}
		else
		{
			if (360.f - Math::FAbs(AI2ball) <= 50.f)
			{
				fbp->MoveForward();
			}
			else
			{
				fbp->StopMoving();
			}
		}

		if (pospos.Dot(fbp->center->axisY) < 20.f && -ball->vel.Dot(fbp->center->axisY) > 10.f)
		{
			if (pospos.Dot(fbp->center->axisX) > 0)
			{
				fbp->KickRight();
			}
			else
			{
				fbp->KickLeft();
			}
		}
		else if (pospos.Length() < 8.f)
		{
			if (pospos.Dot(fbp->center->axisX) > 0)
			{
				fbp->KickLeft();
			}
			else
			{
				fbp->KickRight();
			}
		}
		else
		{
			fbp->StopKickingLeft();
			fbp->StopKickingRight();
		}
	}
	
	

	Vector3 posposgoal = ballpos - fbp->goalie->pos;
	float goalie2ball = Math::RadianToDegree(atan2f(posposgoal.y, posposgoal.x));
	goalie2ball -= fbp->goalie->rot.z + 90.f;

	if (Math::FAbs(goalie2ball) > 8.f && posposgoal.Length() < 80.f)
	{
		if (goalie2ball > 0)
		{
			if (posposgoal.Length() < 25.f)
				fbp->RotateGoalieRight();
			else
				fbp->RotateGoalieLeft();
		}
		else
		{
			if (posposgoal.Length() < 25.f)
				fbp->RotateGoalieLeft();
			else
				fbp->RotateGoalieRight();
		}
	}
	else
	{
		fbp->StopGoalie();
	}
}
