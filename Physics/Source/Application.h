
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include "SoundController.h"

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	static bool IsMousePressed(unsigned short key);
	static void GetCursorPos(double *xpos, double *ypos);
	static bool exitProgram;
	static int GetWindowWidth();
	static int GetWindowHeight();
	static CSoundController* getSoundEngine();


private:
	Application();
	~Application();

	//Declare a window object
	StopWatch m_timer;

	//Sound Engine
	static CSoundController* soundengine;
};

#endif