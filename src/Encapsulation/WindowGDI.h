#pragma once
#include "Window.h"

class WindowGDI : public Window {
public:
    WindowGDI();
	virtual ~WindowGDI();

    void initWindow(HINSTANCE hInstance, int nCmdShow) override;
    HWND getWindowHandle() const override;
    void setGraphic(Graphic* gfx) override;

private:
    HWND hwnd;  // Fenêtre Windows native
    HDC hdc;    // Device Context pour GDI
};
