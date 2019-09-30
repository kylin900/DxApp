#include "App.h"

App::App(HINSTANCE hInstance)
	:
	wnd(hInstance, L"Test", 800, 600)
{
}

App::~App()
{
}

int App::Run()
{
	MSG msg;
	while(GetMessage(&msg, nullptr, 0, 0))
	{
		if(!TranslateAccelerator(msg.hwnd, 0, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}
