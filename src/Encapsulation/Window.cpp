#include "pch.h"
#include "Window.h"

Window::Window()
{
}
Window::~Window()
{
}

void Window::initWindow(HINSTANCE hInstance, int nCmdShow)
{
}

HWND Window::getWindowHandle() const
{
	return HWND();
}

void Window::draw(Ball* ball) const {
    if (graphic) {
        graphic->clear();
        graphic->draw(ball);
        graphic->display();
    }
}

void Window::setGraphic(Graphic* gfx)
{
}
