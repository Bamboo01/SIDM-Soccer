#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include "Mtx44.h"

struct GameObject
{
	enum GAMEOBJECT_TYPE
	{
		GO_NONE = 0,
		GO_BALL,
		GO_PILLAR,
		GO_WALL,
		GO_MOVING_WALL,
		GO_GOAL,
		GO_AIGOAL,
		GO_CUBE,
		GO_ASTEROID,
		GO_SHIP,
		GO_BULLET,
		GO_DADDYASTEROID,
		GO_ENEMY, //enemy ship
		GO_ENEMY_BULLET, //enemy bullet
		GO_MISSILE, //player missile
		GO_POWERUP, //powerup ite
		GO_BLACKHOLE,
		GO_REPULSOR,
		GO_MINISHIP,
		GO_TOTAL, //must be last
	};
	GAMEOBJECT_TYPE type;

	Vector3 pos;
	Vector3 center;

	Vector3 vel;
	Vector3 scale;
	Vector3 rot;

	Vector3 dir;
	Vector3 axisX;
	Vector3 axisY;
	Vector3 displacedPosition;
	float momentOfInertia;
	float momentumCoefficient;
	Vector3 angularVelocity; //in degrees
	float frictionCoefficient;

	GameObject* parent;

	bool active;
	float mass;

	const float timetoshoot = 1.f;
	float timertoshoot = 0.f;

	bool gravity;

	Vector3 color;

	GameObject(GAMEOBJECT_TYPE typeValue = GO_BALL);
	~GameObject();

	void Reset()
	{
		scale = Vector3(1, 1, 1);
		active = false,
		mass = 1.f,
		momentOfInertia = 1.f,
		angularVelocity = Vector3(0, 0, 0);
		color = Vector3(1, 1, 1);
		gravity = false;
	}
};

#endif