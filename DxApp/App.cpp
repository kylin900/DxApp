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
	MSG msg = {0};
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update();
			Draw();
		}
	}
	return (int)msg.wParam;
}

void App::Update()
{
}

void App::Draw()
{
	wnd.Gfx().ClearBuffer();
	wnd.Gfx().Test(1.0f, 0.0f, 0.0f, 0.0f);
	wnd.Gfx().EndFrame();
}
