
#include "GameObject.h"

GameObject::GameObject(GAMEOBJECT_TYPE typeValue)
	: type(typeValue),
	scale(1, 1, 1),
	active(false),
	mass(1.f),
	momentOfInertia(1.f),
	angularVelocity(Vector3(0, 0, 0)),
	color(1, 1, 1),
	gravity(false),
	parent(nullptr),
	momentumCoefficient(1.f),
	frictionCoefficient(0.f)
{
}

GameObject::~GameObject()
{
}