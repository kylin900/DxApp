#pragma once

#include "Window.h"

class App
{
public:
	App(HINSTANCE hInstance);
	~App();
	int Run();

private:
	Window wnd;
};

