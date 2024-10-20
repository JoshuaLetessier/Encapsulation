#pragma once

#ifdef _SFML

#include "Window.h"
class WindowSFML : public Window {
public:
    WindowSFML();
	virtual ~WindowSFML();

    void initWindow(HINSTANCE hInstance, int nCmdShow) override;
    HWND getWindowHandle() const override;
    void setGraphic(Graphic* gfx) override;

    sf::RenderWindow& getWindow();

private:
    sf::RenderWindow window;
    HWND hwnd;

};

#endif // _SFML