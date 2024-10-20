#include "pch.h"
#include "WindowGDI.h"

#include "GraphicGDI.h"

WindowGDI::WindowGDI()
{
}

WindowGDI::~WindowGDI()
{
    if (hwnd && hdc) {
        ReleaseDC(hwnd, hdc);  // Libérer le HDC à la fermeture de la fenêtre
        DestroyWindow(hwnd);
    }
}
	

void WindowGDI::initWindow(HINSTANCE hInstance, int nCmdShow) {
    hwnd = CreateWindowW(L"WinAppClass", L"GDI Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600, nullptr, nullptr, hInstance, nullptr);

    if (!hwnd) {
        MessageBox(nullptr, L"Failed to create window", L"Error", MB_OK);
        return;
    }


    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    hdc = GetDC(hwnd);
}

HWND WindowGDI::getWindowHandle() const {
    return hwnd;
}

void WindowGDI::setGraphic(Graphic* gfx) {
    GraphicGDI* graphicGDI = dynamic_cast<GraphicGDI*>(gfx);

    if (graphicGDI) {
        graphic = graphicGDI;
        graphicGDI->hdc = hdc;  // Utiliser le Device Context pour dessiner avec GDI
    }
}