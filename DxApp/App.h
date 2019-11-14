#pragma once

#include "Window.h"
#include "Timer.h"
#include "Drawable.h"
#include "Box.h"
#include "SkinnedBox.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"

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
	float speed_factor = 1.0f;
	Camera cam;
	PointLight light;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	static constexpr size_t nDrawables = 180;
};

