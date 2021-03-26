#pragma once
#include "FootballPlayer.h"
class AIController
{
public:
	AIController();
	~AIController();
	void Init(FootballPlayer* fbp);
	void Update(float dt, GameObject* ballpos);
	FootballPlayer* fbp;
};

