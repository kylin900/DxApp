#pragma once
#include "stdafx.h"
#include "resource.h"
#include "Graphics.h"
#include <memory>

class Window
{
public:
	Window();
	Window(HINSTANCE hInstance, LPCWSTR titleName, int width, int height);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	Graphics& Gfx();
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HWND hWnd;
	LPCWSTR szWindowClass = L"MyEngine";
	std::unique_ptr<Graphics> gfx;
};

