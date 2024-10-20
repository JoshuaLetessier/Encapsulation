#include "pch.h"

#ifdef _SFML

#include "WindowSFML.h"

#include "GraphicSFML.h"

WindowSFML::WindowSFML()
{
}

WindowSFML::~WindowSFML()
{
    if (window.isOpen()) {
        window.close();  // Fermer proprement la fenêtre SFML
    }
    if (hwnd) {
        DestroyWindow(hwnd);  // Détruire la fenêtre Windows native
    }
}

void WindowSFML::initWindow(HINSTANCE hInstance, int nCmdShow) {
    // Cr�ation de la fen�tre Windows native
    hwnd = CreateWindowW(L"WinAppClass", L"SFML Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600, nullptr, nullptr, hInstance, nullptr);

    if (!hwnd) {
        MessageBox(nullptr, L"Failed to create window", L"Error", MB_OK);
        return;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    window.create(hwnd);  // Liaison avec SFML via le handle de fen�tre Windows
    window.setVerticalSyncEnabled(false);
}

HWND WindowSFML::getWindowHandle() const {
    return hwnd;
}

void WindowSFML::setGraphic(Graphic* gfx) {
    GraphicSFML* graphicSFML = dynamic_cast<GraphicSFML*>(gfx);

    if (graphicSFML) {
        graphic = graphicSFML;

        if (hwnd) {
            graphicSFML->window = &window;  // Lier la fen�tre SFML avec la fen�tre Windows
        }
    }
}

sf::RenderWindow& WindowSFML::getWindow()
{
    return window;
}

#endif // _SFML