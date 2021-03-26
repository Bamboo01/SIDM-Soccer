#include "SceneBase.h"

class SceneMenu : public SceneBase
{
	float m_worldHeight;
	float m_worldWidth;
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	virtual Scene* Clone() { return new SceneMenu(*this); }

	//Hardcoding timers
	float balltimer = 0;
	float texttimer = 0;
	float menushow = 0;

	float rt = 0;
	float gt = 0;
	float bt = 0;
};