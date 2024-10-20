#pragma once
#include "App.h"

#include "WindowGDI.h"
#include "GraphicGDI.h"

class AppGDI :
    public App
{
public:
    AppGDI();
    virtual ~AppGDI();

	virtual void Init(HINSTANCE hInstance, int nCmdShow) override;
	virtual void Render() override;
	virtual void RenderObject() override;
	virtual void RenderDebugInfo() override;

private:
    WindowGDI* window;
    GraphicGDI* graphics;
    HDC hdcBackBuffer;
    HBITMAP hbmBackBuffer;

    HDC memDC;
};