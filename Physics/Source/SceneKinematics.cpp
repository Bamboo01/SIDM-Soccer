#include "SceneKinematics.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

SceneKinematics::SceneKinematics()
{
}

SceneKinematics::~SceneKinematics()
{
}

void SceneKinematics::Init()
{
	SceneBase::Init();

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_speed = 1.f;
	
	m_gravity.Set(0, -9.8f, 0); //init gravity as 9.8ms-2 downwards
	Math::InitRNG();

	m_ghost = new GameObject(GameObject::GO_BALL);

	for (int i = 0; i < 500; i++)
	{
		m_goList.push_back(new GameObject(GameObject::GO_BALL));
	}

	for (int i = 0; i < 50; i++)
	{
		GameObject* cube = new GameObject(GameObject::GO_BALL);
		m_goList.push_back(cube);
		m_cubeList.push_back(cube);
	}

	//Exercise 1: construct 10 GameObject with type GO_BALL and add into m_goList
}

void SceneKinematics::Update(double dt)
{
	SceneBase::Update(dt);

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();


	//Keyboard Section
	if(Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	if(Application::IsKeyPressed(VK_OEM_PLUS))
	{
		//Exercise 6: adjust simulation speed
		m_speed += dt;
	}
	if(Application::IsKeyPressed(VK_OEM_MINUS))
	{
		//Exercise 6: adjust simulation speed
		m_speed -= dt;
	}
	if(Application::IsKeyPressed('c'))
	{
		//Exercise 9: clear screen
		for (GameObject* go : m_goList)
		{
			go->active = false;
		}
	}
	if(Application::IsKeyPressed(' '))
	{
		//Exercise 9: spawn balls
	}
	if(Application::IsKeyPressed('v'))
	{
		//Exercise 9: spawn obstacles
	}

	//Mouse Section
	static bool bLButtonState = false;

	if (m_ghost->active == true)
	{
		x = x / w * m_worldWidth;
		y = (h - y) / h * m_worldHeight;
		m_ghost->vel = m_ghost->pos - Vector3(x, y, 0);
	}

	//Exercise 10: ghost code here
	if(!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
		x = x / w * m_worldWidth;
		y = (h - y) / h * m_worldHeight;
		m_ghost->active = true;
		m_ghost->pos = Vector3(x, y, 0);
		
		////Exercise 4: spawn ball
		//for (GameObject* go : m_goList)
		//{
		//	if (!go->active && go->type == GameObject::GO_BALL)
		//	{
		//		go->active = true;
		//		x = x / w * m_worldWidth;
		//		y = (h - y) / h * m_worldHeight;
		//		go->pos = 
		//		go->vel = Vector3(10, 20, 0);
		//		return;
		//	}
		//}
	}
	else if(bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;
		

		//Exercise 10: replace Exercise 4 code and use ghost to determine ball velocity
		if (m_ghost->active == true)
		{

			for (GameObject* go : m_goList)
			{
				if (!go->active && go->type == GameObject::GO_BALL)
				{
					go->active = true;
					go->pos = m_ghost->pos;
					go->vel = m_ghost->vel;
					m_ghost->active = false;
					return;
				}
			}

		}

		//Exercise 11: kinematics equation
		//v = u + a * t
		//t = (v - u ) / a

		//v * v = u * u + 2 * a * s
		//s = - (u * u) / (2 * a)
						
		//s = u * t + 0.5 * a * t * t
		//(0.5 * a) * t * t + (u) * t + (-s) = 0
	}
	
	static bool bRButtonState = false;
	if(!bRButtonState && Application::IsMousePressed(1))
	{
		bRButtonState = true;
		std::cout << "RBUTTON DOWN" << std::endl;

		auto cube = std::find_if(m_goList.begin(), m_goList.end(), [](const GameObject* go) {return (go->type == GameObject::GO_CUBE && go->active == false);});
		if (cube == m_goList.end())
		{
			GameObject* tempCube = new GameObject(GameObject::GO_CUBE);
			m_goList.push_back(tempCube);
			m_cubeList.push_back(tempCube);
		}
		for (GameObject* go : m_goList)
		{
			if (!go->active && go->type == GameObject::GO_CUBE)
			{
				go->active = true;
				x = x / w * m_worldWidth;
				y = (h - y) / h * m_worldHeight;
				go->pos = Vector3(x, y, 0);
				return;
			}
		}

	}
	else if(bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
		std::cout << "RBUTTON UP" << std::endl;
	}

	//Physics Simulation Section
	fps = (float)(1.f / dt);

	//Exercise 11: update kinematics information
	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			if(go->type == GameObject::GO_BALL)
			{
				//Exercise 2: implement equation 1 & 2
				go->vel += m_gravity * dt * m_speed;
				go->pos += go->vel * dt * m_speed;
				//Exercise 12: replace Exercise 2 code and use average speed instead
			}

			//Exercise 8: check collision with GO_CUBE
			if (go->type == GameObject::GO_BALL)
			{
				for (GameObject* cube : m_cubeList)
				{
					if ((cube->pos - go->pos).Length() <= 3)
					{
						/*go->active = false;*/
						go->vel = -go->vel;
						continue;
					}
				}
			}
			
			//Exercise 5: unspawn ball when outside window
			int w = Application::GetWindowWidth();
			int h = Application::GetWindowHeight();
			if (
				go->pos.x > m_worldWidth 
				|| go->pos.x < 0
				|| go->pos.y > m_worldHeight
				|| go->pos.y < 0
				)
			{
				std::cout << "MAN DOWN" << std::endl;
				go->active = false;
			}
		}
	}
}

void SceneKinematics::RenderGO(GameObject *go)
{
	switch(go->type)
	{
	case GameObject::GO_BALL:
		//Exercise 3: render a sphere with radius 1
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		RenderMesh(meshList[GEO_BALL], true);
		modelStack.PopMatrix();
		break;
	case GameObject::GO_CUBE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		RenderMesh(meshList[GEO_CUBE], true);
		modelStack.PopMatrix();
		//Exercise 7: render a cube with length 2
		break;
	}
}

void SceneKinematics::Render()
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

	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			RenderGO(go);
		}
	}
	if(m_ghost->active)
	{
		RenderGO(m_ghost);
	}

	//On screen text
	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 3);
	
	//Exercise 6: print simulation speed
	
	//Exercise 10: print m_ghost position and velocity information

	//Exercise 11: print kinematics information

	RenderTextOnScreen(meshList[GEO_TEXT], "Kinematics", Color(0, 1, 0), 3, 0, 0);
	RenderTextOnScreen(meshList[GEO_TEXT], "Speed: " + std::to_string(m_speed), Color(0, 1, 0), 3, 0, 6);
}

void SceneKinematics::Exit()
{
	// Cleanup VBO
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if(meshList[i])
			delete meshList[i];
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	
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
}
