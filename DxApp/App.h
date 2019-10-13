#pragma once

#include "Window.h"
#include "Timer.h"
#include "Drawable.h"
#include "Box.h"

class App
{
public:
	App(HINSTANCE hInstance);
	int Run();

private:
	void DoFrame();
private:	
	Window wnd;
	Timer timer;
	std::vector<std::unique_ptr<Box>> boxes;
};

