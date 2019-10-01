#pragma once

#include "Window.h"

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
};

