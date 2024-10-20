#include "pch.h"
#ifdef _SFML


#include "AppSFML.h"

#include "BallManager.h"


AppSFML::AppSFML()
{
	window = new WindowSFML();
	graphics = new GraphicSFML();
}

AppSFML::~AppSFML()
{
	std::cout << "AppSFML destructor called" << std::endl;
	if (window)
		delete window;
	if (graphics)
		delete graphics;
	if (hWnd)
		DestroyWindow(hWnd);
}

void AppSFML::Init(HINSTANCE hInstance, int nCmdShow)
{
	//Create the main window
	window->initWindow(hInstance, nCmdShow);
	hWnd = window->getWindowHandle();
	if (hWnd == NULL) return;
}

void AppSFML::Render()
{
	RenderObject();	
	RenderDebugInfo();
	window->getWindow().display();
}

void AppSFML::RenderObject()
{
	if (window)
	{
		window->getWindow().clear(sf::Color::White);


		window->setGraphic(graphics);

		// Si ballManager est initialisé et il y a des balles, on les affiche
		if (ballManager && ballManager->getBalls().size() > 0)
		{
			for (auto& ball : ballManager->getBalls())
			{
				if (graphics) {
					graphics->loadTexture(&ball);
					graphics->draw(&ball);
				}
			}
		}
	}
	else
	{
		MessageBox(NULL, L"Window not found", L"Error", MB_OK);
		return;
	}
}

void AppSFML::RenderDebugInfo()
{
	sf::Font font;
	std::string fontPath = "..\\..\\..\\..\\..\\res\\arial.ttf";
#ifdef _DEBUG
	fontPath = "..\\..\\..\\res\\arial.ttf";
#endif
	if (!font.loadFromFile(fontPath)) {
		MessageBox(NULL, L"Font not found", L"Error", MB_OK);
		return;
	}

	sf::Text debugText;
	debugText.setFont(font);
	debugText.setCharacterSize(16);
	debugText.setFillColor(sf::Color::Black);
	debugText.setPosition(10.f, 10.f);

	// Pr�parer les informations de d�bogage
	std::ostringstream debugStream;
	debugStream << "FPS: " << fps << "\n"
		<< "Desired FPS: " << desiredFramerate << "\n"
		<< "Current Balls: " << ballManager->getBalls().size() << "\n"
		<< "Total Balls: " << countBallList << "\n"
		<< "Total Time (s): " << elapsedTotalSeconds;

	debugText.setString(debugStream.str());

	window->getWindow().draw(debugText);
}

WindowSFML* AppSFML::getWindow()
{
	return window;
}

#endif // _SFMl