#pragma once

#include "Window.h"
#include "Timer.h"
#include "Drawable.h"
#include "Box.h"
#include "SkinnedBox.h"
#include "ImguiManager.h"
#include "Camera.h"

class App
{
public:
	App(HINSTANCE hInstance);
	int Run();

private:
	void DoFrame();
private:	
	ImguiManager imgui;
	Window wnd;
	Timer timer;
	std::vector<std::unique_ptr<SkinnedBox>> boxes;
	float speed_factor = 1.0f;
	Camera cam;
};

