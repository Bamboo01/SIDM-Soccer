#include "Application.h"
#include "GL\glew.h"
#include "SceneManager.h"

void SceneMenu::Init()
{
	SceneBase::Init();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	Application::getSoundEngine()->PlaySoundByID(0);
}

void SceneMenu::Update(double dt)
{
	m_worldHeight = 200.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	SceneBase::Update(dt);

	if (balltimer < 3.f)
	{
		balltimer += dt;
	}

	if (texttimer < 6.5f)
	{
		texttimer += dt;
	}


	if (rt < 1.f)
	{
		rt += dt * 0.5;
	}
	else
	{
		rt = 0;
	}
	if (gt < 1.f)
	{
		gt += dt;
	}
	else
	{
		gt = 0;
	}
	if (bt < 1.f)
	{
		bt += dt * 0.2;
	}
	else
	{
		bt = 0;
	}
	
	menushow += dt;
	if (menushow > 8.5f)
	{
		if (Application::IsKeyPressed(VK_RETURN))
		{
			SceneManager::getInstance()->ChangeScene(SCENE_FOOTBALL);
		}
	}
}

void SceneMenu::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (menushow < 8.f)
	{
		camera.target.Set(0, 0, 1);
		camera.position.Set(0, 0, 00);
		camera.up.Set(0, 1, 0);
		Mtx44 projection;
		projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 20000.f);
		projectionStack.LoadMatrix(projection);
		viewStack.LoadIdentity();
		viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
		SceneBase::Render();

		modelStack.LoadIdentity();



		modelStack.PushMatrix();
		modelStack.Translate(-5 * balltimer, 5 * balltimer, 20 * balltimer);
		modelStack.Scale(5.f, 5.f, 5.f);
		RenderMesh(meshList[GEO_FOOTBALL], false);
		modelStack.PopMatrix();


		if (texttimer >= 1.f)
		{
			modelStack.PushMatrix();
			modelStack.Translate(20, 3 * balltimer, 20 * balltimer);
			modelStack.Scale(4.f, 4.f, 4.f);
			modelStack.Rotate(170, 0, 1, 0);
			RenderText(meshList[GEO_TEXT], "SUPER", Color(rt, gt, bt));
			modelStack.PopMatrix();
		}

		if (texttimer >= 3.f)
		{
			modelStack.PushMatrix();
			modelStack.Translate(20, 1 * (texttimer - balltimer), 20 * (texttimer - balltimer));
			modelStack.Scale(4.f, 4.f, 4.f);
			modelStack.Rotate(170, 0, 1, 0);
			RenderText(meshList[GEO_TEXT], "SIDM SOCCER", Color(rt, gt, bt));
			modelStack.PopMatrix();
		}
	}
	else
	{
		Mtx44 projection;
		projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
		projectionStack.LoadMatrix(projection);
		camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));
		viewStack.LoadIdentity();
		viewStack.LookAt(
			camera.position.x, camera.position.y, camera.position.z,
			camera.target.x, camera.target.y, camera.target.z,
			camera.up.x, camera.up.y, camera.up.z
		);
		modelStack.LoadIdentity();

		modelStack.PushMatrix();
		modelStack.Translate(0.5f * m_worldWidth, 0.5f * m_worldHeight, 0);
		modelStack.Scale(m_worldWidth, m_worldHeight, 0);
		RenderMesh(meshList[GEO_IWANNADIE], false);
		modelStack.PopMatrix();
	}

}

void SceneMenu::Exit()
{
	SceneBase::Exit();
	Application::getSoundEngine()->PauseSoundByID(0);
}
