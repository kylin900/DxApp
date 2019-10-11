#pragma once

#include "Window.h"
#include "Timer.h"

class App
{
public:
	App(HINSTANCE hInstance);
	~App();
	int Run();

private:
	void Update();
	void Draw();
private:	
	Window wnd;
	Timer timer;
};

