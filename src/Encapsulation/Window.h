#pragma once

#include "Graphic.h"

class Window {
public:

    Window();
    virtual ~Window();

    virtual void initWindow(HINSTANCE hInstance, int nCmdShow);
    virtual HWND getWindowHandle() const;
    void draw(Ball* ball) const;
    virtual void setGraphic(Graphic* gfx);
protected:
    Graphic* graphic;
};

