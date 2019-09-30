#pragma once
#include "stdafx.h"
#include "resource.h"

class Window
{
public:
	Window(HINSTANCE hInstance, LPCWSTR titleName, int width, int height);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HWND hWnd;
	LPCWSTR szWindowClass = L"MyEngine";
};

