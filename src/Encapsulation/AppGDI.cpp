#include "pch.h"
#include "AppGDI.h"
#include "BallManager.h"

#include "BallManager.h"

AppGDI::AppGDI()
{
	window = new WindowGDI();
	
}

AppGDI::~AppGDI()
{
	delete window;
	delete graphics;
}

void AppGDI::Init(HINSTANCE hInstance, int nCmdShow)
{
	//Create the main window
	window->initWindow(hInstance, nCmdShow);
	hWnd = window->getWindowHandle();
	if (hWnd == NULL) return;
}

void AppGDI::Render()
{
    if (window) {
        HDC hdc = GetDC(window->getWindowHandle());
        if (hdc) {
            RECT rect;
            GetClientRect(window->getWindowHandle(), &rect);

            // Double buffering: créer un DC et un bitmap compatibles avec l'écran
            memDC = CreateCompatibleDC(hdc);
            HBITMAP hbmMem = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
            HGDIOBJ hOldBitmap = SelectObject(memDC, hbmMem);

            // Effacer le fond du buffer mémoire (fond blanc)
            HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
            FillRect(memDC, &rect, hBrush);
            DeleteObject(hBrush);

            // Appeler les fonctions de rendu
            RenderObject();       // Dessiner les objets (rectangles, etc.)
            RenderDebugInfo();    // Dessiner les informations de debug

            // Copier le contenu du buffer mémoire sur l'écran
            BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);

            // Libérer les ressources
            SelectObject(memDC, hOldBitmap);
            DeleteObject(hbmMem);
            DeleteDC(memDC);
            ReleaseDC(window->getWindowHandle(), hdc);
        }
    }
}


void AppGDI::RenderObject() {
     // Dessiner les bitmaps des balles
    if (ballManager && ballManager->getBalls().size() > 0) {
        graphics = new GraphicGDI(memDC);
        for (auto& ball : ballManager->getBalls()) {
            if (graphics) {
                graphics->draw(&ball);  // Utiliser draw pour dessiner les bitmaps
            }
        }
    }
}


void AppGDI::RenderDebugInfo() {
    SetTextColor(memDC, RGB(0, 0, 0));   // Couleur du texte (noir)
    SetBkMode(memDC, TRANSPARENT);       // Fond transparent pour le texte

    // Préparer les informations de débogage
    std::ostringstream debugStream;
    debugStream << "FPS: " << fps << "\n"
        << "Desired FPS: " << desiredFramerate << "\n"
        << "Current Balls: " << ballManager->getBalls().size() << "\n"
        << "Total Balls: " << countBallList << "\n"
        << "Total Time (s): " << elapsedTotalSeconds;

    std::string debugString = debugStream.str();
    int yOffset = 10;

    // Afficher chaque ligne de texte
    std::istringstream stream(debugString);
    std::string line;
    while (std::getline(stream, line)) {
        TextOutA(memDC, 10, yOffset, line.c_str(), line.length());
        yOffset += 20;  // Décalage vertical pour chaque ligne de texte
    }
}

