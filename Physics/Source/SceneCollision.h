#ifndef SCENE_COLLISION_H
#define SCENE_COLLISION_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include "PlayerController.h"
#include "AIController.h"

class SceneCollision : public SceneBase
{
public:
	SceneCollision();
	~SceneCollision();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	virtual Scene* Clone() { return new SceneCollision(*this); }

	void RenderGO(GameObject *go);

	GameObject* FetchGO();
	void ReturnGO(GameObject *go);
protected:

	//Physics
	std::vector<GameObject *> m_goList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	GameObject *m_ghost;
	int m_objectCount;

	//Auditing
	float m1, m2;
	Vector3 u1, u2, v1, v2;
	
	//Paddles and stuff
	GameObject* paddleL;
	GameObject* paddleR;

	//Game
	PlayerController player;
	AIController ai;
	GameObject* football;
	GameObject* sdfootball1;
	GameObject* sdfootball2;
	GameObject* sdfootball3;
	GameObject* sdfootball4;
	GameObject* wheel1;
	GameObject* wheel2;
	GameObject* wheel3;
	GameObject* wheel4;
	GameObject* L;
	GameObject* R;
	GameObject* U;
	GameObject* D;
	GameObject* playerGoal;
	GameObject* playerGoalL;
	GameObject* playerGoalR;
	GameObject* aiGoal;
	GameObject* aiGoalL;
	GameObject* aiGoalR;

	void CollisionResponse(GameObject* go, GameObject* go2, float dt);

	//GameState
	enum GameState
	{
		STATE_INGAME,
		STATE_RESET,
		STATE_PLAYERSCORED,
		STATE_AISCORED,
		STATE_WIN,
		STATE_LOSE,
		NUM_STATE
	};
	
	//stuff
	float timer = 0;
	float matchtimer = 0;
	int playerscore;
	int aiscore;

	GameState gamestate;

	//Color
	Vector3 color;
};

#endif


