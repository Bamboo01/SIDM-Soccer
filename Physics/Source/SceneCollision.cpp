#include "SceneCollision.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>
#include "SceneManager.h"

SceneCollision::SceneCollision()
{
}

SceneCollision::~SceneCollision()
{
}

void SceneCollision::Init()
{
	SceneBase::Init();
	Application::getSoundEngine()->PlaySoundByID(1);
	//Physics code here
	matchtimer = 0;
	m_speed = 1.f;
	playerscore = 0;
	aiscore = 0;
	Math::InitRNG();

	////Exercise 1: initialize m_objectCount
	//m_objectCount = 0;

	m_ghost = new GameObject(GameObject::GO_BALL);

	m_worldHeight = 200.f;
	m_worldWidth = 266.666656;

	gamestate = GameState::STATE_INGAME;

	wheel1 = FetchGO();
	wheel1->type = GameObject::GO_MOVING_WALL;
	wheel1->active = true;
	wheel1->pos = Vector3(m_worldWidth / 2, (m_worldHeight / 2) + 50, 0);
	wheel1->scale = Vector3(30, 4, 1);
	wheel1->rot = Vector3(0, 0, 0);
	wheel1->color = Vector3(0.6, 0.1, 0.1);
	wheel1->angularVelocity = Vector3(0, 0, 30);
	wheel1->mass = 5.5f;

	wheel2 = FetchGO();
	wheel2->type = GameObject::GO_MOVING_WALL;
	wheel2->active = true;
	//wheel2->pos = Vector3(m_worldWidth / 2, m_worldHeight / 2 + 30.f, 0);
	wheel2->parent = wheel1;
	wheel2->scale = Vector3(30, 4, 1);
	wheel2->rot = Vector3(0, 0, 90);
	wheel2->color = Vector3(0.6, 0.1, 0.1);
	//wheel2->angularVelocity = Vector3(0, 0, 30);
	wheel2->mass = 5.5f;

	wheel3 = FetchGO();
	wheel3->type = GameObject::GO_MOVING_WALL;
	wheel3->active = true;
	wheel3->pos = Vector3(m_worldWidth / 2, (m_worldHeight / 2) - 50, 0);
	wheel3->scale = Vector3(30, 4, 1);
	wheel3->rot = Vector3(0, 0, 0);
	wheel3->color = Vector3(0.6, 0.1, 0.1);
	wheel3->angularVelocity = Vector3(0, 0, 30);
	wheel3->mass = 5.5f;

	wheel4 = FetchGO();
	wheel4->type = GameObject::GO_MOVING_WALL;
	wheel4->active = true;
	//wheel4->pos = Vector3(m_worldWidth / 2, m_worldHeight / 2 + 30.f, 0);
	wheel4->parent = wheel3;
	wheel4->scale = Vector3(30, 4, 1);
	wheel4->rot = Vector3(0, 0, 90);
	wheel4->color = Vector3(0.6, 0.1, 0.1);
	//wheel4->angularVelocity = Vector3(0, 0, 30);
	wheel4->mass = 5.5f;

	football = FetchGO();
	football->type = GameObject::GO_BALL;
	football->active = true;
	football->pos = Vector3(m_worldWidth / 2, (m_worldHeight / 2), 0);
	football->scale = Vector3(3, 3, 3);
	football->vel.SetZero();
	football->color = Vector3(1, 1, 1);
	football->mass = 27;
	football->frictionCoefficient = 0.05f;

	sdfootball1 = FetchGO();
	sdfootball1->type = GameObject::GO_BALL;
	sdfootball1->active = false;
	sdfootball1->pos = Vector3((m_worldWidth / 2) + 10, (m_worldHeight / 2) + 10, 0);
	sdfootball1->scale = Vector3(3, 3, 3);
	sdfootball1->vel.SetZero();
	sdfootball1->color = Vector3(1, 1, 1);
	sdfootball1->mass = 27;
	sdfootball1->frictionCoefficient = 0.05f;

	sdfootball2 = FetchGO();
	sdfootball2->type = GameObject::GO_BALL;
	sdfootball2->active = false;
	sdfootball2->pos = Vector3((m_worldWidth / 2) - 10, (m_worldHeight / 2) + 10, 0);
	sdfootball2->scale = Vector3(3, 3, 3);
	sdfootball2->vel.SetZero();
	sdfootball2->color = Vector3(1, 1, 1);
	sdfootball2->mass = 27;
	sdfootball2->frictionCoefficient = 0.05f;

	sdfootball3 = FetchGO();
	sdfootball3->type = GameObject::GO_BALL;
	sdfootball3->active = false;
	sdfootball3->pos = Vector3((m_worldWidth / 2) + 10, (m_worldHeight / 2) - 10, 0);
	sdfootball3->scale = Vector3(3, 3, 3);
	sdfootball3->vel.SetZero();
	sdfootball3->color = Vector3(1, 1, 1);
	sdfootball3->mass = 27;
	sdfootball3->frictionCoefficient = 0.05f;

	sdfootball4 = FetchGO();
	sdfootball4->type = GameObject::GO_BALL;
	sdfootball4->active = false;
	sdfootball4->pos = Vector3((m_worldWidth / 2) - 10, (m_worldHeight / 2) - 10, 0);
	sdfootball4->scale = Vector3(3, 3, 3);
	sdfootball4->vel.SetZero();
	sdfootball4->color = Vector3(1, 1, 1);
	sdfootball4->mass = 27;
	sdfootball4->frictionCoefficient = 0.05f;

	L = FetchGO();
	L->type = GameObject::GO_WALL;
	L->active = true;
	L->pos = Vector3(0, 0, 0);
	L->scale = Vector3(999, 10, 1);
	L->rot = Vector3(0, 0, -90);
	L->color = Vector3(0.6, 0.1, 0.1);
	L->momentumCoefficient = 0.6f;

	R = FetchGO();
	R->type = GameObject::GO_WALL;
	R->active = true;
	R->pos = Vector3(m_worldWidth, 0, 0);
	R->scale = Vector3(999, 10, 1);
	R->rot = Vector3(0, 0, 90);
	R->color = Vector3(0.6, 0.1, 0.1);
	R->momentumCoefficient = 0.6f;

	U = FetchGO();
	U->type = GameObject::GO_WALL;
	U->active = true;
	U->pos = Vector3(0, m_worldHeight, 0);
	U->scale = Vector3(999, 10, 1);
	U->rot = Vector3(0, 0, 180);
	U->color = Vector3(0.6, 0.1, 0.1);
	U->momentumCoefficient = 0.6f;

	D = FetchGO();
	D->type = GameObject::GO_WALL;
	D->active = true;
	D->pos = Vector3(0, 0, 0);
	D->scale = Vector3(999, 10, 1);
	D->rot = Vector3(0, 0, 0);
	D->color = Vector3(0.6, 0.1, 0.1);
	D->momentumCoefficient = 0.6f;



	playerGoal = FetchGO();
	playerGoal->type = GameObject::GO_GOAL;
	playerGoal->active = true;
	playerGoal->center.Set(0, 5, 0);
	playerGoal->pos = Vector3(5, (m_worldHeight / 2), 0);
	playerGoal->scale = Vector3(30, 10, 1);
	playerGoal->rot = Vector3(0, 0, -90);
	playerGoal->color.Set(0, 1, 0);

	playerGoalL = FetchGO();
	playerGoalL->type = GameObject::GO_WALL;
	playerGoalL->active = true;
	playerGoalL->center.Set(7.5, 0, 0);
	playerGoalL->pos = Vector3(5, (m_worldHeight / 2) + 15, 0);
	playerGoalL->scale = Vector3(15, 7.5, 1);
	playerGoalL->color = Vector3(0.6, 0.1, 0.1);

	playerGoalR = FetchGO();
	playerGoalR->type = GameObject::GO_WALL;
	playerGoalR->active = true;
	playerGoalR->center.Set(7.5, 0, 0);
	playerGoalR->pos = Vector3(5, (m_worldHeight / 2) - 15, 0);
	playerGoalR->scale = Vector3(15, 7.5, 1);
	playerGoalR->color = Vector3(0.6, 0.1, 0.1);

	aiGoal = FetchGO();
	aiGoal->type = GameObject::GO_AIGOAL;
	aiGoal->active = true;
	aiGoal->center.Set(0, 5, 0);
	aiGoal->pos = Vector3(m_worldWidth - 5, (m_worldHeight / 2), 0);
	aiGoal->scale = Vector3(30, 10, 1);
	aiGoal->rot = Vector3(0, 0, 90);
	aiGoal->color.Set(1, 0, 0);

	aiGoalL = FetchGO();
	aiGoalL->type = GameObject::GO_WALL;
	aiGoalL->active = true;
	aiGoalL->center.Set(-7.5, 0, 0);
	aiGoalL->pos = Vector3(m_worldWidth - 5, (m_worldHeight / 2) + 15, 0);
	aiGoalL->scale = Vector3(15, 7.5, 1);
	aiGoalL->color = Vector3(0.6, 0.1, 0.1);

	aiGoalR = FetchGO();
	aiGoalR->type = GameObject::GO_WALL;
	aiGoalR->active = true;
	aiGoalR->center.Set(-7.5, 0, 0);
	aiGoalR->pos = Vector3(m_worldWidth - 5, (m_worldHeight / 2) - 15, 0);
	aiGoalR->scale = Vector3(15, 7.5, 1);
	aiGoalR->color = Vector3(0.6, 0.1, 0.1);

	//players
	FootballPlayer* p1 = new FootballPlayer;
	p1->Init(FetchGO(), FetchGO(), FetchGO(), FetchGO());
	player.Init(p1);
	player.fbp->center->pos.Set(80.f, 0.5f * m_worldHeight, 0);
	player.fbp->center->rot.Set(0, 0, -90);
	player.fbp->goalie->pos.Set(40.f, 0.5f * m_worldHeight, 0);
	player.fbp->goalie->rot.Set(0, 0, 180);
	player.fbp->center->color.Set(0, 1, 0);
	player.fbp->paddleL->color.Set(0, 1, 0);
	player.fbp->paddleL->color.Set(0, 1, 0);
	player.fbp->paddleR->color.Set(0, 1, 0);
	player.fbp->goalie->color.Set(0, 1, 0);

	FootballPlayer* p2 = new FootballPlayer;
	p2->Init(FetchGO(), FetchGO(), FetchGO(), FetchGO());
	ai.Init(p2);
	ai.fbp->center->pos.Set(m_worldWidth - 80.f, 0.5f * m_worldHeight, 0);
	ai.fbp->center->rot.Set(0, 0, 90);
	ai.fbp->goalie->rot.Set(0, 0, 180);
	ai.fbp->goalie->pos.Set(m_worldWidth - 40.f, 0.5f * m_worldHeight, 0);	

	{
		GameObject* wally = FetchGO();
		wally->type = GameObject::GO_MOVING_WALL;
		wally->active = true;
		wally->center.Set(-15, 0, 0);
		wally->pos = Vector3(25, m_worldHeight - 5, 0);
		wally->scale = Vector3(30, 4, 1);
		wally->rot = Vector3(0, 0, 45);
		wally->color = Vector3(0.0, 0.5, 0.5);
		wally->momentumCoefficient = 1.5f;
	}
	{
		GameObject* wally = FetchGO();
		wally->type = GameObject::GO_MOVING_WALL;
		wally->active = true;
		wally->center.Set(15, 0, 0);
		wally->pos = Vector3(25, 5, 0);
		wally->scale = Vector3(30, 4, 1);
		wally->rot = Vector3(0, 0, 135);
		wally->color = Vector3(0.0, 0.5, 0.5);
		wally->momentumCoefficient = 1.5f;
	}
	{
		GameObject* wally = FetchGO();
		wally->type = GameObject::GO_MOVING_WALL;
		wally->active = true;
		wally->center.Set(15, 0, 0);
		wally->pos = Vector3(m_worldWidth - 25, m_worldHeight - 5, 0);
		wally->scale = Vector3(30, 4, 1);
		wally->rot = Vector3(0, 0, -45);
		wally->color = Vector3(0.0, 0.5, 0.5);
		wally->momentumCoefficient = 1.5f;
	}
	{
		GameObject* wally = FetchGO();
		wally->type = GameObject::GO_MOVING_WALL;
		wally->active = true;
		wally->center.Set(-15, 0, 0);
		wally->pos = Vector3(m_worldWidth - 25, 5, 0);
		wally->scale = Vector3(30, 4, 1);
		wally->rot = Vector3(0, 0, -135);
		wally->color = Vector3(0.0, 0.5, 0.5);
		wally->momentumCoefficient = 1.5f;
	}

	{
		float r = 50;
		for (int i = 0; i < 12; i++)
		{
			float ang = Math::DegreeToRadian((i * 2.5) + 20.f);
			GameObject* barrel = FetchGO();
			barrel->type = GameObject::GO_PILLAR;
			barrel->active = true;
			barrel->pos = Vector3((m_worldWidth / 2) + (r * cosf(ang)), (m_worldHeight / 2) + (r * sinf(ang)), 0);
			barrel->scale = Vector3(4, 4, 1);
			barrel->color = Vector3(0.6, 0.1, 0.1);
			barrel->momentumCoefficient = 0.6f;
		}
	}

	{
		float r = -50;
		for (int i = 0; i < 12; i++)
		{
			float ang = Math::DegreeToRadian((i * 2.5) + 20.f);
			GameObject* barrel = FetchGO();
			barrel->type = GameObject::GO_PILLAR;
			barrel->active = true;
			barrel->pos = Vector3((m_worldWidth / 2) + (r * cosf(ang)), (m_worldHeight / 2) + (r * sinf(ang)), 0);
			barrel->scale = Vector3(4, 4, 1);
			barrel->color = Vector3(0.6, 0.1, 0.1);
			barrel->momentumCoefficient = 0.6f;
		}
	}

	{
		float r = 80;
		for (int i = 0; i < 18; i++)
		{
			float ang = Math::DegreeToRadian((i * 2) + 20.f);
			GameObject* barrel = FetchGO();
			barrel->type = GameObject::GO_PILLAR;
			barrel->active = true;
			barrel->pos = Vector3((m_worldWidth / 2) - (r * cosf(ang)), (m_worldHeight / 2) + (r * sinf(ang)), 0);
			barrel->scale = Vector3(4, 4, 1);
			barrel->color = Vector3(0.6, 0.1, 0.1);
			barrel->momentumCoefficient = 0.6f;
		}
	}

	{
		float r = 80;
		for (int i = 0; i < 18; i++)
		{
			float ang = Math::DegreeToRadian((i * 2) + 20.f);
			GameObject* barrel = FetchGO();
			barrel->type = GameObject::GO_PILLAR;
			barrel->active = true;
			barrel->center = Vector3((m_worldWidth / 2), (m_worldHeight / 2), 0);
			barrel->pos = Vector3((m_worldWidth / 2) + (r * cosf(ang)), (m_worldHeight / 2) - (r * sinf(ang)), 0);
			barrel->scale = Vector3(4, 4, 1);
			barrel->color = Vector3(0.6, 0.1, 0.1);
			barrel->momentumCoefficient = 0.6f;
		}
	}

	{
		GameObject* barrel = FetchGO();
		barrel->type = GameObject::GO_PILLAR;
		barrel->active = true;
		barrel->pos = Vector3((m_worldWidth / 2), (m_worldHeight / 2) + 25, 0);
		barrel->scale = Vector3(4, 4, 1);
		barrel->color = Vector3(0.6, 0.1, 0.1);
		barrel->momentumCoefficient = 0.6f;
	}

	{
		GameObject* barrel = FetchGO();
		barrel->type = GameObject::GO_PILLAR;
		barrel->active = true;
		barrel->pos = Vector3((m_worldWidth / 2), (m_worldHeight / 2) - 25, 0);
		barrel->scale = Vector3(4, 4, 1);
		barrel->color = Vector3(0.6, 0.1, 0.1);
		barrel->momentumCoefficient = 0.6f;
	}
}

GameObject* SceneCollision::FetchGO()
{
	//Exercise 2a: implement FetchGO()
	m_objectCount++;

	//std::vector<GameObject*>::iterator it = std::find_if
	//(
	//	m_goList.begin(),
	//	m_goList.end(),
	//	[](const GameObject* go) 
	//	{
	//		return (go->active == false); 
	//	}
	//);

	GameObject* thing = nullptr;

	//if (it == m_goList.end())
	//{
	//	thing = new GameObject(GameObject::GO_BALL);
	//	m_goList.push_back(thing);
	//	
	//}
	//else
	//{
	//	thing = (GameObject*)*it;
	//}
	thing = new GameObject(GameObject::GO_BALL);
	m_goList.push_back(thing);
	thing->active = true;
	return thing;
}

void SceneCollision::ReturnGO(GameObject *go)
{
	//Exercise 3: implement ReturnGO()
	if (go->active == true)
	{
		go->Reset();
		m_objectCount--;
	}
}

#pragma region
bool ballballCollisionCheck(GameObject* go, GameObject* go2)
{
	Vector3 relativeVel = go->vel - go2->vel;
	Vector3 displacmentVec = go2->pos - go->pos;

	return
		(fabs(displacmentVec.x) <= go->scale.x + go2->scale.x) &&
		(fabs(displacmentVec.y) <= go->scale.x + go2->scale.x) &&
		(-displacmentVec).Dot(relativeVel) <= 0;
}

bool ballpillarCollisionCheck(GameObject* ball, GameObject* pillar)
{
	Vector3 relativeVel = -ball->vel;
	Vector3 displacmentVec = pillar->pos - ball->pos;

	return
		(fabs(displacmentVec.x) <= ball->scale.x + pillar->scale.x) &&
		(fabs(displacmentVec.y) <= ball->scale.x + pillar->scale.x) && 
		(-displacmentVec).Dot(ball->vel) < 0;
}

bool ballwallCollisionCheck(GameObject* ball, GameObject* wall)
{
	Mtx44 rotx;
	Mtx44 roty;
	Mtx44 rotz;
	Mtx44 finalrotation;
	rotx.SetToIdentity();
	rotx.SetToRotation(wall->rot.x, 1, 0, 0);
	roty.SetToIdentity();
	roty.SetToRotation(wall->rot.y, 0, 1, 0);
	rotz.SetToIdentity();
	rotz.SetToRotation(wall->rot.z, 0, 0, 1);
	finalrotation = rotx * roty * rotz;

	wall->displacedPosition = wall->pos + (finalrotation * wall->center);

	wall->axisX = finalrotation * Vector3(1, 0, 0);
	wall->axisY = finalrotation * Vector3(0, 1, 0);

	Vector3 RPos = ball->pos - wall->displacedPosition;

	wall->axisX.Normalize();
	wall->axisY.Normalize();

	wall->dir = wall->axisY;


	//Checking four corners
	Vector3 UpL = wall->displacedPosition;
	UpL -= (wall->scale.x * 0.5) * wall->axisX;
	UpL += (wall->scale.y * 0.5) * wall->axisY;

	Vector3 UpR = wall->displacedPosition;
	UpR += (wall->scale.x * 0.5) * wall->axisX;
	UpR += (wall->scale.y * 0.5) * wall->axisY;

	Vector3 BotL = wall->displacedPosition;
	BotL -= (wall->scale.x * 0.5) * wall->axisX;
	BotL -= (wall->scale.y * 0.5) * wall->axisY;

	Vector3 BotR = wall->displacedPosition;
	BotR += (wall->scale.x * 0.5) * wall->axisX;
	BotR -= (wall->scale.y * 0.5) * wall->axisY;

	Vector3 axisY = wall->axisY;

	//if (RPos.Dot(axisY) > 0)
	//	axisY = -axisY;

	bool collided = (
		fabs((wall->scale.x * 0.5)) + fabs((ball->scale.x)) > fabs(RPos.Dot(wall->axisX)) &&
		fabs((wall->scale.y * 0.5)) + fabs((ball->scale.x)) > fabs(RPos.Dot(wall->axisY))
		//ball->vel.Dot(axisY) >= 0
		)
		||
		(
		((BotR - ball->pos).Length() < ball->scale.x && (BotR - ball->pos).Dot(ball->vel) <= 0) ||
		((BotL - ball->pos).Length() < ball->scale.x && (BotL - ball->pos).Dot(ball->vel) <= 0) ||
		((UpR - ball->pos).Length() < ball->scale.x && (UpR - ball->pos).Dot(ball->vel) <= 0) ||
		((UpL - ball->pos).Length() < ball->scale.x && (UpL - ball->pos).Dot(ball->vel) <= 0))
		;

	return collided;
}

bool CheckCollision(GameObject* go, GameObject* go2)
{
	if (go == go2)
	{
		//This shouldn't happen, but JUST in case heh
		return false;
	}

	bool collided = false;

	switch(go->type)
	{
	case GameObject::GO_BALL:
		if (go2->type == GameObject::GO_BALL)
		{
			collided = ballballCollisionCheck(go, go2);
		}
		else if (go2->type == GameObject::GO_WALL || go2->type == GameObject::GO_MOVING_WALL || go2->type == GameObject::GO_GOAL || go2->type == GameObject::GO_AIGOAL)
		{
			collided = ballwallCollisionCheck(go, go2);
		}
		else if (go2->type == GameObject::GO_PILLAR)
		{
			collided = ballpillarCollisionCheck(go, go2);
		}
		break;
	case GameObject::GO_GOAL:
	case GameObject::GO_AIGOAL:
	case GameObject::GO_MOVING_WALL:
	case GameObject::GO_WALL:
		if (go2->type == GameObject::GO_BALL)
		{
			collided = ballwallCollisionCheck(go2, go);
		}
		break;

	case GameObject::GO_PILLAR:
		if (go2->type == GameObject::GO_BALL)
		{
			collided = ballpillarCollisionCheck(go2, go);
		}
		break;
	default:
		collided = false;
		break;
	}

	return collided;
}

void ballwallCollisionResponse(GameObject* ball, GameObject* wall, float dt)
{
	Vector3 RPos = ball->pos - wall->pos;

	Vector3 IntersectionPoint;
	IntersectionPoint.Set(
		Math::Clamp(fabs(RPos.Dot(wall->axisX)), (0.5f * wall->scale.x) - fabs(wall->center.x), (0.5f * wall->scale.x) + fabs(wall->center.x)),
		Math::Clamp(fabs(RPos.Dot(wall->axisY)), (0.5f * wall->scale.y) - fabs(wall->center.y), (0.5f * wall->scale.y) + fabs(wall->center.y)),
		0);

	RPos = ball->pos - wall->displacedPosition;

	float xIntersectionPoint = fabs(RPos.Dot(wall->axisX)) - ball->scale.x;
	float yIntersectionPoint = fabs(RPos.Dot(wall->axisY)) - ball->scale.y;

	float xPenLength = fabs((0.5f * wall->scale.x) - fabs(xIntersectionPoint));
	float yPenLength = fabs((0.5f * wall->scale.y) - fabs(yIntersectionPoint));

	Vector3 normal;

	Vector3 ang2lin;
	float coefficient = 1.f;

	bool isOnNegativeX = false;
	bool isOnNegativeY = false;

	if (RPos.Dot(wall->axisX) < 0)
	{
		isOnNegativeX = true;
	}
	if (RPos.Dot(wall->axisY) < 0)
	{
		isOnNegativeY = true;
	}

	if (xPenLength < yPenLength)
	{
		normal = wall->axisX;
		if (isOnNegativeX)
		{
			normal = -normal;
		}
	}
	else
	{
		normal = wall->axisY;
		if (isOnNegativeY)
		{
			normal = -normal;
		}
	}

	/*Ensure they are no longer in contact*/

	bool dothething = true;
	float distofcontact = 0.f;
	if (xPenLength < yPenLength)
	{
		Vector3 xaxis = wall->axisX;
		if (isOnNegativeX)
		{
			xaxis = -xaxis;
		}
		//Fake physics
		dothething = false;
		ball->pos += xPenLength * xaxis;
	}
	else
	{
		Vector3 yaxis = wall->axisY;
		if (isOnNegativeY)
		{
			yaxis = -yaxis;
		}
		//Fake physics
		ball->pos += yPenLength * yaxis;
	}


	if (wall->angularVelocity.Length() > 0 && dothething == true)
	{
		Vector3 angvel = wall->angularVelocity;
		angvel.z = Math::DegreeToRadian(angvel.z);
		angvel = (1 + wall->momentumCoefficient) * angvel * IntersectionPoint.x;
		ang2lin = angvel.Length() * normal;
		coefficient = wall->momentumCoefficient;
	}

	Vector3 vel = ball->vel;
	ball->vel =
		(vel - ((1 + wall->momentumCoefficient) * vel.Dot(normal)) * normal)
		+ ang2lin;
	ball->vel += ((1 + wall->momentumCoefficient) * wall->vel).Dot(normal) * normal;
}

void ballpillarCollisionResponse(GameObject* ball, GameObject* pillar)
{
	Vector3 normal = (ball->pos - pillar->pos).Normalized();
	Vector3 vel = ball->vel;

	ball->vel = vel - (((1 + pillar->momentumCoefficient) * vel.Dot(normal)) * normal);
	ball->vel += ((1 + pillar->momentumCoefficient) * pillar->vel).Dot(normal)* normal;
}

void ballballCollisionResponse(GameObject* go, GameObject* go2)
{
	Vector3 govel;
	Vector3 go2vel;

	govel =
		go->vel -
		(
		((go2->mass * 2) / (go->mass + go2->mass)) *
			((go->vel - go2->vel).Dot(go->pos - go2->pos) * (1.f / pow((go->pos - go2->pos).Length(), 2))) *
			(go->pos - go2->pos)
			);

	go2vel =
		go2->vel -
		(
		((go->mass * 2) / (go2->mass + go->mass)) *
			((go2->vel - go->vel).Dot(go2->pos - go->pos) * (1.f / pow((go2->pos - go->pos).Length(), 2))) *
			(go2->pos - go->pos)
			);

	go->vel = govel;
	go2->vel = go2vel;
}

void SceneCollision::CollisionResponse(GameObject* go, GameObject* go2, float dt)
{
	if (go == go2)
	{
		//This shouldn't happen, but JUST in case heh
		return;
	}

	switch (go->type)
	{
	case GameObject::GO_BALL:
		if (go2->type == GameObject::GO_BALL)
		{
			Application::getSoundEngine()->PlaySoundByID(2);
			ballballCollisionResponse(go, go2);
		}
		else if (go2->type == GameObject::GO_WALL || go2->type == GameObject::GO_MOVING_WALL)
		{
			Application::getSoundEngine()->PlaySoundByID(2);
			ballwallCollisionResponse(go, go2, dt);
		}
		else if (go2->type == GameObject::GO_GOAL)
		{
			Application::getSoundEngine()->PlaySoundByID(3);
			aiscore++;
			gamestate = GameState::STATE_AISCORED;
		}
		else if (go2->type == GameObject::GO_AIGOAL)
		{
			Application::getSoundEngine()->PlaySoundByID(3);
			playerscore++;
			gamestate = GameState::STATE_PLAYERSCORED;
		}
		else if (go2->type == GameObject::GO_PILLAR)
		{
			Application::getSoundEngine()->PlaySoundByID(2);
			ballpillarCollisionResponse(go, go2);
		}
		break;
	case GameObject::GO_GOAL:
		if (go2->type == GameObject::GO_BALL)
		{
			Application::getSoundEngine()->PlaySoundByID(3);
			playerscore++;
			gamestate = GameState::STATE_AISCORED;
		}
		break;
	case GameObject::GO_AIGOAL:
		if (go2->type == GameObject::GO_BALL)
		{
			Application::getSoundEngine()->PlaySoundByID(3);
			aiscore++;
			gamestate = GameState::STATE_PLAYERSCORED;
		}
		break;
	case GameObject::GO_MOVING_WALL:
	case GameObject::GO_WALL:
		if (go2->type == GameObject::GO_BALL)
		{
			Application::getSoundEngine()->PlaySoundByID(2);
			ballwallCollisionResponse(go2, go, dt);
		}
		break;
	case GameObject::GO_PILLAR:
		if (go2->type == GameObject::GO_BALL)
		{
			Application::getSoundEngine()->PlaySoundByID(2);
			ballpillarCollisionResponse(go2, go);
		}
		break;
	default:
		break;
	}
}
#pragma endregion lazy collision

void SceneCollision::Update(double dt)
{
	if (playerscore > 3)
	{
		timer += dt;
		gamestate = GameState::STATE_WIN;
		if (Application::IsKeyPressed(VK_RETURN))
		{
			SceneManager::getInstance()->ChangeScene(SCENE_MAINMENU);
		}
	}
	if (aiscore > 3)
	{
		timer += dt;
		gamestate = GameState::STATE_LOSE;
		if (Application::IsKeyPressed(VK_RETURN))
		{
			SceneManager::getInstance()->ChangeScene(SCENE_MAINMENU);
		}
	}
	SceneBase::Update(dt);
	if (gamestate == STATE_INGAME)
	{
		m_speed = 1;
		matchtimer += dt;
		player.Update(dt, football);
		ai.Update(dt, football);

		if (matchtimer > 20)
		{
			sdfootball1->active = true;
			sdfootball2->active = true;
			sdfootball3->active = true;
			sdfootball4->active = true;
		}

		//if (Application::IsKeyPressed('9'))
		//{
		//	m_speed = Math::Max(-1.f, m_speed - 0.1f);
		//}
		//if (Application::IsKeyPressed('0'))
		//{
		//	m_speed += 0.1f;
		//}

		double x, y;
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		x = x / w * m_worldWidth;
		y = (h - y) / h * m_worldHeight;

		////Saving velocity
		//if (m_ghost->active == true)
		//{
		//	m_ghost->vel = m_ghost->pos - Vector3(x, y, 0);
		//	if (m_ghost->vel.IsZero())
		//	{
		//		m_ghost->scale = Vector3(0.01, 0.01, 0.01);
		//	}
		//	else
		//	{
		//		m_ghost->scale = Vector3(m_ghost->vel.Length() * 0.2f, m_ghost->vel.Length() * 0.2f, 1);
		//	}
		//	m_ghost->color = color;
		//}

		//Mouse Section
		//static bool bLButtonState = false;
		//if (!bLButtonState && Application::IsMousePressed(0))
		//{
		//	bLButtonState = true;
		//	std::cout << "LBUTTON DOWN" << std::endl;
		//	m_ghost->active = true;
		//	m_ghost->pos = Vector3(x, y, 0);
		//}
		//else if (bLButtonState && !Application::IsMousePressed(0))
		//{
		//	bLButtonState = false;
		//	std::cout << "LBUTTON UP" << std::endl;

		//	//Exercise 6: spawn small GO_BALL
		//	if (m_ghost->active == true)
		//	{
		//		if (color.x < 1)
		//		{
		//			color.x += 0.1;
		//		}
		//		else
		//		{
		//			if (color.y < 1)
		//			{
		//				color.y += 0.1;
		//			}
		//			else
		//			{
		//				if (color.z < 1)
		//				{
		//					color.z += 0.1;
		//				}
		//				else
		//				{
		//					color = Vector3(1, 1, 1);
		//				}
		//			}
		//		}
		//		m_ghost->active = false;
		//		GameObject* go = FetchGO();
		//		go->active = true;
		//		go->pos = m_ghost->pos;
		//		go->vel = m_ghost->vel;
		//		go->type = GameObject::GO_BALL;
		//		go->scale = Vector3(m_ghost->vel.Length() * 0.2f, m_ghost->vel.Length() * 0.2f, 1);
		//		go->mass = m_ghost->vel.Length() * 3.f;
		//		go->color = color;
		//		go->gravity = true;
		//		return;
		//	}
		//}
		//static bool bRButtonState = false;

		//if (!bRButtonState && Application::IsMousePressed(1))
		//{
		//	bRButtonState = true;
		//	std::cout << "RBUTTON DOWN" << std::endl;
		//	m_ghost->active = true;
		//	m_ghost->pos = Vector3(x, y, 0);
		//}
		//else if (bRButtonState && !Application::IsMousePressed(1))
		//{
		//	bRButtonState = false;
		//	std::cout << "RBUTTON UP" << std::endl;

		//	//Exercise 10: spawn large GO_BALL
		//	if (m_ghost->active == true)
		//	{
		//		if (color.x < 1)
		//		{
		//			color.x += 0.1;
		//		}
		//		else
		//		{
		//			if (color.y < 1)
		//			{
		//				color.y += 0.1;
		//			}
		//			else
		//			{
		//				if (color.z < 1)
		//				{
		//					color.z += 0.1;
		//				}
		//				else
		//				{
		//					color = Vector3(1, 1, 1);
		//				}
		//			}
		//		}

		//		m_ghost->active = false;
		//		GameObject* go = FetchGO();
		//		go->active = true;
		//		go->pos = m_ghost->pos;
		//		go->vel = m_ghost->vel;
		//		go->scale = Vector3(3, 3, 3);
		//		go->type = GameObject::GO_BALL;
		//		go->mass = 27;
		//		go->color = color;
		//		go->gravity = true;
		//		return;
		//	}
		//}

		//Physics Simulation Section

		int checks = 0;

		for (std::vector<GameObject*>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
		{
			GameObject* go = (GameObject*)*it;
			if (go->active)
			{
				if (
					player.fbp->center->pos.x > m_worldWidth + 5 || player.fbp->center->pos.x < -5 ||
					player.fbp->center->pos.y > m_worldHeight + 5 || player.fbp->center->pos.y < -5
					)
				{
					aiscore++;
					gamestate = GameState::STATE_AISCORED;
					Application::getSoundEngine()->PlaySoundByID(3);
					return;
				}

				if (
					ai.fbp->center->pos.x > m_worldWidth + 5 || ai.fbp->center->pos.x < -5 ||
					ai.fbp->center->pos.y > m_worldHeight + 5 || ai.fbp->center->pos.y < -5
					)
				{
					playerscore++;
					gamestate = GameState::STATE_PLAYERSCORED;
					Application::getSoundEngine()->PlaySoundByID(3);
					return;
				}

				if (
					football->pos.x > m_worldWidth - 5 || football->pos.x < 5 ||
					football->pos.y > m_worldHeight - 5 || football->pos.y < 5
					)
				{
					football->type = GameObject::GO_BALL;
					football->active = true;
					football->pos = Vector3(m_worldWidth / 2, (m_worldHeight / 2), 0);
					football->scale = Vector3(4, 4, 1);
					football->color = Vector3(1, 1, 1);
					football->vel.SetZero();
				}

				if (
					football->pos.x > m_worldWidth - 5 || football->pos.x < 5 ||
					football->pos.y > m_worldHeight - 5 || football->pos.y < 5
					)
				{
					football->type = GameObject::GO_BALL;
					football->active = true;
					football->pos = Vector3(m_worldWidth / 2, (m_worldHeight / 2), 0);
					football->scale = Vector3(4, 4, 1);
					football->color = Vector3(1, 1, 1);
					football->vel.SetZero();
				}

				if (
					sdfootball1->pos.x > m_worldWidth - 5 || sdfootball1->pos.x < 5 ||
					sdfootball1->pos.y > m_worldHeight - 5 || sdfootball1->pos.y < 5
					)
				{
					sdfootball1->type = GameObject::GO_BALL;
					sdfootball1->pos = Vector3((m_worldWidth / 2) + 10, (m_worldHeight / 2) + 10, 0);
					sdfootball1->scale = Vector3(3, 3, 3);
					sdfootball1->vel.SetZero();
					sdfootball1->mass = 27;
					sdfootball1->frictionCoefficient = 0.05f;
				}

				if (
					sdfootball2->pos.x > m_worldWidth - 5 || sdfootball2->pos.x < 5 ||
					sdfootball2->pos.y > m_worldHeight - 5 || sdfootball2->pos.y < 5
					)
				{
					sdfootball2->type = GameObject::GO_BALL;
					sdfootball2->pos = Vector3((m_worldWidth / 2) - 10, (m_worldHeight / 2) + 10, 0);
					sdfootball2->scale = Vector3(3, 3, 3);
					sdfootball2->vel.SetZero();
					sdfootball2->mass = 27;
					sdfootball2->frictionCoefficient = 0.05f;
				}

				if (
					sdfootball3->pos.x > m_worldWidth - 5 || sdfootball3->pos.x < 5 ||
					sdfootball3->pos.y > m_worldHeight - 5 || sdfootball3->pos.y < 5
					)
				{
					sdfootball3->type = GameObject::GO_BALL;
					sdfootball3->pos = Vector3((m_worldWidth / 2) + 10, (m_worldHeight / 2) - 10, 0);
					sdfootball3->scale = Vector3(3, 3, 3);
					sdfootball3->vel.SetZero();
					sdfootball3->mass = 27;
					sdfootball3->frictionCoefficient = 0.05f;
				}

				if (
					sdfootball4->pos.x > m_worldWidth - 5 || sdfootball4->pos.x < 5 ||
					sdfootball4->pos.y > m_worldHeight - 5 || sdfootball4->pos.y < 5
					)
				{
					sdfootball4->type = GameObject::GO_BALL;
					sdfootball4->pos = Vector3((m_worldWidth / 2) - 10, (m_worldHeight / 2) - 10, 0);
					sdfootball4->scale = Vector3(3, 3, 3);
					sdfootball4->vel.SetZero();
					sdfootball4->mass = 27;
					sdfootball4->frictionCoefficient = 0.05f;
				}



				//For parenting stuff
				Mtx44 finalrotation;
				finalrotation.SetToIdentity();
				if (go->parent)
				{
					//If it works it works
					Mtx44 rotx;
					Mtx44 roty;
					Mtx44 rotz;
					rotx.SetToIdentity();
					rotx.SetToRotation(go->parent->rot.x, 1, 0, 0);
					roty.SetToIdentity();
					roty.SetToRotation(go->parent->rot.y, 0, 1, 0);
					rotz.SetToIdentity();
					rotz.SetToRotation(go->parent->rot.z, 0, 0, 1);
					finalrotation = rotx * roty * rotz;
				}

				//Lazy, rushing
				Mtx44 arotx;
				Mtx44 aroty;
				Mtx44 arotz;
				Mtx44 afinalrotation;
				arotx.SetToIdentity();
				arotx.SetToRotation(go->rot.x, 1, 0, 0);
				aroty.SetToIdentity();
				aroty.SetToRotation(go->rot.y, 0, 1, 0);
				arotz.SetToIdentity();
				arotz.SetToRotation(go->rot.z, 0, 0, 1);
				afinalrotation = arotx * aroty * arotz * finalrotation;

				go->axisX = afinalrotation * Vector3(1, 0, 0);
				go->axisY = afinalrotation * Vector3(0, 1, 0);

				go->axisX.Normalize();
				go->axisY.Normalize();

				go->dir = go->axisY;
				Vector3 temprot = go->rot;
				Vector3 tempvel = go->vel;
				if (go->parent)
				{
					go->pos = go->parent->pos + (afinalrotation * go->parent->center);
					go->rot += go->parent->rot;
					go->vel += go->parent->vel;
					go->angularVelocity += go->parent->angularVelocity;
				}

				

				//Rotation checks
				if (temprot.z >= 360.f)
				{
					temprot.z = 0;
				}
				if (temprot.z <= -360.f)
				{
					temprot.z = 0;
				}

				int w = Application::GetWindowWidth();
				int h = Application::GetWindowHeight();
				if (go->type == GameObject::GO_BALL)
				{
					if (go->pos.x > m_worldWidth - go->scale.x || go->pos.x < go->scale.x || go->pos.y > m_worldHeight - go->scale.x || go->pos.y < go->scale.x)
					{
						ReturnGO(go);
						continue;
					}
				}

				for (std::vector<GameObject*>::iterator it2 = it; it2 != m_goList.end(); ++it2)
				{
					if (it2 == it)
					{
						continue;
					}

					GameObject* go2 = (GameObject*)*it2;
					if (!go2->active)
					{
						continue;
					}

					//DISGUSTING

									//For parenting stuff
					Mtx44 finalrotation2;
					finalrotation2.SetToIdentity();
					if (go->parent)
					{
						//If it works it works
						Mtx44 rotx2;
						Mtx44 roty2;
						Mtx44 rotz2;
						rotx2.SetToIdentity();
						rotx2.SetToRotation(go->parent->rot.x, 1, 0, 0);
						roty2.SetToIdentity();
						roty2.SetToRotation(go->parent->rot.y, 0, 1, 0);
						rotz2.SetToIdentity();
						rotz2.SetToRotation(go->parent->rot.z, 0, 0, 1);
						finalrotation2 = rotx2 * roty2 * rotz2;
					}

					//Lazy, rushing
					Mtx44 arotx2;
					Mtx44 aroty2;
					Mtx44 arotz2;
					Mtx44 afinalrotation2;
					arotx2.SetToIdentity();
					arotx2.SetToRotation(go2->rot.x, 1, 0, 0);
					aroty2.SetToIdentity();
					aroty2.SetToRotation(go2->rot.y, 0, 1, 0);
					arotz2.SetToIdentity();
					arotz2.SetToRotation(go2->rot.z, 0, 0, 1);
					afinalrotation2 = arotx2 * aroty2 * arotz2 * finalrotation2;

					go2->axisX = afinalrotation2 * Vector3(1, 0, 0);
					go2->axisY = afinalrotation2 * Vector3(0, 1, 0);

					go2->axisX.Normalize();
					go2->axisY.Normalize();

					go2->dir = go2->axisY;
					Vector3 temprot2 = go2->rot;
					if (go2->parent)					
					{
						go2->pos = go2->parent->pos + (afinalrotation2 * go2->parent->center);
						go2->rot += go2->parent->rot;
						go2->vel += go2->parent->vel;
						go2->angularVelocity += go2->parent->angularVelocity;
					}

					//Rotation checks
					if (temprot2.z >= 360.f)
					{
						temprot2.z = 0;
					}
					if (temprot2.z <= -360.f)
					{
						temprot2.z = 0;
					}

					bool collided = CheckCollision(go, go2);
					if (collided)
					{
						CollisionResponse(go, go2, dt);
					}

					go2->rot = temprot2;
					if (go2->parent)
					{
						go2->vel -= go2->parent->vel;
						go2->angularVelocity -= go2->parent->angularVelocity;
					}
				}

				if (go->parent)
				{
					go->vel -= go->parent->vel;
					go->angularVelocity -= go->parent->angularVelocity;
				}

				//This is disgusting, but I cannot help it till I have my own stuff set up LOL
				//Only reason this works cuz no transfer of angular momentum
				go->rot = temprot;

				if (!go->vel.IsZero())
				{
					go->vel -= (go->frictionCoefficient * (go->mass * 9.8f) * dt) * go->vel.Normalized();
				}
				
				go->pos += go->vel * dt * m_speed;
				go->rot += go->angularVelocity * dt * m_speed;
			}
		}
		//std::cout << "Collisions checked in this frame =  " << checks << std::endl;
	}
	else if (gamestate == GameState::STATE_AISCORED)
	{
		m_speed = 0;
		timer += dt;

		if (timer > 3.f)
		{
			gamestate = GameState::STATE_RESET;
		}
	}
	else if (gamestate == GameState::STATE_PLAYERSCORED)
	{
		m_speed = 0;
		timer += dt;

		if (timer > 3.f)
		{
			gamestate = GameState::STATE_RESET;
		}
	}
	else if (gamestate == GameState::STATE_RESET)
	{
		timer = 0;
		matchtimer = 0;
		player.fbp->center->pos.Set(80.f, 0.5f * m_worldHeight, 0);
		player.fbp->center->rot.Set(0, 0, -90);
		player.fbp->goalie->pos.Set(40.f, 0.5f * m_worldHeight, 0);
		player.fbp->goalie->rot.Set(0, 0, 180);
		player.fbp->center->color.Set(0, 1, 0);
		player.fbp->paddleL->color.Set(0, 1, 0);
		player.fbp->paddleL->color.Set(0, 1, 0);
		player.fbp->paddleR->color.Set(0, 1, 0);
		player.fbp->goalie->color.Set(0, 1, 0);

		ai.fbp->center->pos.Set(m_worldWidth - 80.f, 0.5f * m_worldHeight, 0);
		ai.fbp->center->rot.Set(0, 0, 90);
		ai.fbp->goalie->pos.Set(m_worldWidth - 40.f, 0.5f * m_worldHeight, 0);

		football->type = GameObject::GO_BALL;
		football->active = true;
		football->pos = Vector3(m_worldWidth / 2, (m_worldHeight / 2), 0);
		football->scale = Vector3(4, 4, 1);
		football->color = Vector3(1, 1, 1);
		football->vel.SetZero();

		sdfootball1->type = GameObject::GO_BALL;
		sdfootball1->active = false;
		sdfootball1->pos = Vector3((m_worldWidth / 2) + 10, (m_worldHeight / 2) + 10, 0);
		sdfootball1->scale = Vector3(3, 3, 3);
		sdfootball1->vel.SetZero();
		sdfootball1->color = Vector3(1, 1, 1);
		sdfootball1->mass = 27;
		sdfootball1->frictionCoefficient = 0.05f;

		sdfootball2->type = GameObject::GO_BALL;
		sdfootball2->active = false;
		sdfootball2->pos = Vector3((m_worldWidth / 2) - 10, (m_worldHeight / 2) + 10, 0);
		sdfootball2->scale = Vector3(3, 3, 3);
		sdfootball2->vel.SetZero();
		sdfootball2->color = Vector3(1, 1, 1);
		sdfootball2->mass = 27;
		sdfootball2->frictionCoefficient = 0.05f;

		sdfootball3->type = GameObject::GO_BALL;
		sdfootball3->active = false;
		sdfootball3->pos = Vector3((m_worldWidth / 2) + 10, (m_worldHeight / 2) - 10, 0);
		sdfootball3->scale = Vector3(3, 3, 3);
		sdfootball3->vel.SetZero();
		sdfootball3->color = Vector3(1, 1, 1);
		sdfootball3->mass = 27;
		sdfootball3->frictionCoefficient = 0.05f;

		sdfootball4->type = GameObject::GO_BALL;
		sdfootball4->active = false;
		sdfootball4->pos = Vector3((m_worldWidth / 2) - 10, (m_worldHeight / 2) - 10, 0);
		sdfootball4->scale = Vector3(3, 3, 3);
		sdfootball4->vel.SetZero();
		sdfootball4->color = Vector3(1, 1, 1);
		sdfootball4->mass = 27;
		sdfootball4->frictionCoefficient = 0.05f;

		gamestate = GameState::STATE_INGAME;
	}
	else if (gamestate == GameState::STATE_WIN)
	{
		m_speed = 0;
	}
	else if (gamestate == GameState::STATE_LOSE)
	{
		m_speed = 0;
	}
}


void SceneCollision::RenderGO(GameObject *go)
{
	if (go->active == false)
	{
		return;
	}
	modelStack.PushMatrix();
	switch(go->type)
	{
	case GameObject::GO_BALL:
		//Exercise 4: render a sphere using scale and pos
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		//Exercise 11: think of a way to give balls different colors
		glUniform3fv(m_parameters[U_EXTERNAL_COLOR], 1, &go->color.x);
		RenderMesh(meshList[GEO_FOOTBALL], false);
		modelStack.PopMatrix();
		break;
	case GameObject::GO_PILLAR:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		glUniform3fv(m_parameters[U_EXTERNAL_COLOR], 1, &go->color.x);
		RenderMesh(meshList[GEO_BALL], false);
		modelStack.PopMatrix();
		break;
	case GameObject::GO_GOAL:
	case GameObject::GO_AIGOAL:
	case GameObject::GO_MOVING_WALL:
	case GameObject::GO_WALL:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Rotate(go->rot.x, 1, 0, 0);
		modelStack.Rotate(go->rot.y, 0, 1, 0);
		modelStack.Rotate(go->rot.z, 0, 0, 1);
		if (go->parent)
		{
			modelStack.Rotate(go->parent->rot.x, 1, 0, 0);
			modelStack.Rotate(go->parent->rot.y, 0, 1, 0);
			modelStack.Rotate(go->parent->rot.z, 0, 0, 1);
		}
		modelStack.Translate(go->center.x, go->center.y, go->center.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		glUniform3fv(m_parameters[U_EXTERNAL_COLOR], 1, &go->color.x);
		RenderMesh(meshList[GEO_CUBE], false);
		modelStack.PopMatrix();
	default:
		break;
	}
	modelStack.PopMatrix();
}

void SceneCollision::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
						camera.position.x, camera.position.y, camera.position.z,
						camera.target.x, camera.target.y, camera.target.z,
						camera.up.x, camera.up.y, camera.up.z
					);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();
	
	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(0.5f * m_worldWidth, 0.5f * m_worldHeight, 0);
	modelStack.Scale(m_worldWidth, m_worldHeight, 0);
	RenderMesh(meshList[GEO_FIELD], false);
	modelStack.PopMatrix();


	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			RenderGO(go);
		}
	}

	if (m_ghost->active)
	{
		RenderGO(m_ghost);
	}

	//On screen text
	if (gamestate == GameState::STATE_PLAYERSCORED)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Player 1 scored!", Color(0, 1, 0), 5, 5, 20);
	}
	if (gamestate == GameState::STATE_AISCORED)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Player 2 scored!", Color(0, 1, 0), 5, 5, 20);
	}
	if (gamestate == GameState::STATE_WIN)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Player 1 Wins!", Color(0, 1, 0), 4, 5, 20);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press enter to return", Color(0, 1, 0), 3, 5, 15);
	}
	if (gamestate == GameState::STATE_LOSE)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Player 2 Wins!", Color(0, 1, 0), 4, 5, 20);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press enter to return", Color(0, 1, 0), 3, 5, 15);
	}

	RenderTextOnScreen(meshList[GEO_TEXT], "Player 1: " + std::to_string(playerscore), Color(1, 1, 1), 3, 5, 50);
	RenderTextOnScreen(meshList[GEO_TEXT], "Player 2: " + std::to_string(aiscore), Color(1, 1, 1), 3, 45, 50);

	RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((int)matchtimer), Color(1, 1, 1), 4, 40, 45);

	if (matchtimer > 20.f)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Sudden Death!", Color(0, 1, 0), 4, 15, 40);
	}

	//RenderTextOnScreen(meshList[GEO_TEXT], "Number of objects " + std::to_string(m_objectCount), Color(0, 1, 0), 2, 0, 0);

	//std::ostringstream ss2;
	//ss2.precision(3);
	//ss2 << "Speed: " << m_speed;
	//RenderTextOnScreen(meshList[GEO_TEXT], ss2.str(), Color(0, 1, 0), 3, 0, 6);
	//
	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 0);
	
	
}

void SceneCollision::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while(m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
	if(m_ghost)
	{
		delete m_ghost;
		m_ghost = NULL;
	}
	Application::getSoundEngine()->PauseSoundByID(1);
}
