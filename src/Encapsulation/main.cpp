#include "pch.h"
#include "main.h"

#include "AppSFML.h"
#include "AppGDI.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"WinAppClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	if (RegisterClassExW(&wcex) == 0)
		return 0;

	bool running = true;
	MSG msg;

#ifdef _SFML
	AppSFML app;
	app.Init(hInstance, nCmdShow);
	while (running)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				running = false;
				return 0;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		sf::Event event;
		while (app.getWindow()->getWindow().pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Num1)
					app.setDesiredFramerate(30);
				else if (event.key.code == sf::Keyboard::Num2)
					app.setDesiredFramerate(60);
				else if (event.key.code == sf::Keyboard::Num3)
					app.setDesiredFramerate(120);
			}
		}
		app.Run();
	}

#elif _GDI	
	AppGDI app;
	app.Init(hInstance, nCmdShow);


	while (running)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				running = false;
				return 0;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (GetAsyncKeyState('1') & 0x8000) {
			app.setDesiredFramerate(30);
		}
		else if (GetAsyncKeyState('2') & 0x8000) {
			app.setDesiredFramerate(60);
		}
		else if (GetAsyncKeyState('3') & 0x8000) {
			app.setDesiredFramerate(120);
		}

		app.Run();
	}
#endif // 

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif


	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int id = LOWORD(wParam);
		int notif = HIWORD(wParam);
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	case WM_PAINT:
	{
//#ifdef _SFML
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
//#elif _GDI
//		PAINTSTRUCT ps;
//		HDC hdc = BeginPaint(hWnd, &ps);
//		EndPaint(hWnd, &ps);
//		break;
//#endif
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
