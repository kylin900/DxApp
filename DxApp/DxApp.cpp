// DxApp.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "DxApp.h"
#include "App.h"
#include "DxUtil.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	App app(hInstance);
	try
	{		
		return app.Run();
	}
	catch(DxException& e)
	{
		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
		return 0;
	}
}

