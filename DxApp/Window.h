#pragma once
#include "stdafx.h"
#include "resource.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <memory>

class Window
{
public:
	Window(HINSTANCE hInstance, LPCWSTR titleName, int width, int height);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	Graphics& Gfx();
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);	
public:
	Keyboard kbd;
	Mouse mouse;

private:
	int width;
	int height;
	HWND hWnd;
	LPCWSTR szWindowClass = L"MyEngine";
	std::unique_ptr<Graphics> gfx;
};

