#pragma once

#include "Window.h"
#include "Timer.h"
#include "Drawable.h"
#include "SkinnedBox.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"
#include <set>

class App
{
public:
	App(HINSTANCE hInstance);
	int Run();
	void SpawnSimulationWindow() noexcept;
	void SpawnBoxWindowManagerWindow() noexcept;
	void SpawnBoxWindows() noexcept;

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
	std::vector<class Box*> boxes;
	std::optional<int> comboBoxIndex;
	std::set<int> boxControlIds;
	static constexpr size_t nDrawables = 180;
};

