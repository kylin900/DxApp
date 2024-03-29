#include "Window.h"
#include <memory.h>
#include <optional>
#include "imgui/imgui_impl_win32.h"

static Window* instance;
Window::Window(HINSTANCE hInstance, LPCWSTR titleName, int width, int height)
	:
	width(width),
	height(height)
{
	instance = this;
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = instance->WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DXAPP));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)( COLOR_WINDOW + 1 );
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassExW(&wcex);

	RECT R;
	R.left = 100;
	R.right = width + R.left;
	R.top = 100;
	R.bottom = height + R.top;

	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	hWnd = CreateWindow(szWindowClass, titleName,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, R.right - R.left, R.bottom - R.top, nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	ImGui_ImplWin32_Init(hWnd);
	gfx = std::make_unique<Graphics>(hWnd);
}


Window::~Window()
{
	ImGui_ImplWin32_Shutdown();
	DestroyWindow(hWnd);
}

Graphics & Window::Gfx()
{
	return *gfx;
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return instance->MyWndProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK Window::MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
	{
		return true;
	}
	const auto& imio = ImGui::GetIO();

	switch(message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch(wmId)
		{
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	/*********** KEYBOARD MESSAGES ***********/
	case WM_KEYDOWN:
		// syskey commands need to be handled to track ALT key (VK_MENU) and F10
	case WM_SYSKEYDOWN:
		if(imio.WantCaptureKeyboard)
		{
			break;
		}

		if(!( lParam & 0x40000000 ) || kbd.AutorepeatIsEnabled()) // filter autorepeat
		{
			kbd.OnKeyPressed(static_cast<unsigned char>( wParam ));
		}
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		if(imio.WantCaptureKeyboard)
		{
			break;
		}
		kbd.OnKeyReleased(static_cast<unsigned char>( wParam ));
		break;
	case WM_CHAR:
		if(imio.WantCaptureKeyboard)
		{
			break;
		}
		kbd.OnChar(static_cast<unsigned char>( wParam ));
		break;
		/*********** END KEYBOARD MESSAGES ***********/
		/************* MOUSE MESSAGES ****************/
	case WM_MOUSEMOVE:
	{
		// stifle this mouse message if imgui wants to capture
		if(imio.WantCaptureMouse)
		{
			break;
		}
		const POINTS pt = MAKEPOINTS(lParam);
		// in client region -> log move, and log enter + capture mouse (if not previously in window)
		if(pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height)
		{
			mouse.OnMouseMove(pt.x, pt.y);
			if(!mouse.IsInWindow())
			{
				SetCapture(hWnd);
				mouse.OnMouseEnter();
			}
		}
		// not in client -> log move / maintain capture if button down
		else
		{
			if(wParam & ( MK_LBUTTON | MK_RBUTTON ))
			{
				mouse.OnMouseMove(pt.x, pt.y);
			}
			// button up -> release capture / log event for leaving
			else
			{
				ReleaseCapture();
				mouse.OnMouseLeave();
			}
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		SetForegroundWindow(hWnd);
		// stifle this mouse message if imgui wants to capture
		if(imio.WantCaptureMouse)
		{
			break;
		}
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftPressed(pt.x, pt.y);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		// stifle this mouse message if imgui wants to capture
		if(imio.WantCaptureMouse)
		{
			break;
		}
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightPressed(pt.x, pt.y);
		break;
	}
	case WM_LBUTTONUP:
	{
		// stifle this mouse message if imgui wants to capture
		if(imio.WantCaptureMouse)
		{
			break;
		}
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftReleased(pt.x, pt.y);
		// release mouse if outside of window
		if(pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height)
		{
			ReleaseCapture();
			mouse.OnMouseLeave();
		}
		break;
	}
	case WM_RBUTTONUP:
	{
		// stifle this mouse message if imgui wants to capture
		if(imio.WantCaptureMouse)
		{
			break;
		}
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightReleased(pt.x, pt.y);
		// release mouse if outside of window
		if(pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height)
		{
			ReleaseCapture();
			mouse.OnMouseLeave();
		}
		break;
	}
	case WM_MOUSEWHEEL:
	{
		// stifle this mouse message if imgui wants to capture
		if(imio.WantCaptureMouse)
		{
			break;
		}
		const POINTS pt = MAKEPOINTS(lParam);
		const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		mouse.OnWheelDelta(pt.x, pt.y, delta);
		break;
	}
	/************** END MOUSE MESSAGES **************/
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

