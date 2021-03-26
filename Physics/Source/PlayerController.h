#include "FootballPlayer.h"

#pragma once
class PlayerController
{
public:
	PlayerController();
	~PlayerController();
	void Init(FootballPlayer* fbp);
	void Update(float dt, GameObject* ball);
	FootballPlayer* fbp;

};

