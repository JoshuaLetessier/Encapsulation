#include "pch.h"
#include "App.h"

#include "BallManager.h"

App::App()
{
	ballManager = new BallManager();
	countBallList = 0;
	hWnd = NULL;
	windowWidth = 0;
	windowHeight = 0;

	programStartTime = std::chrono::steady_clock::now();

	// Variables pour calculer les FPS
	startTime = programStartTime;
	frameCount = 0;

}

App::~App()
{
	delete ballManager;
}

void App::Run()
{
	frameCount++;
	currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsed = currentTime - startTime;

	if (elapsed.count() >= 1.0f) {
		fps = frameCount;
		frameCount = 0;
		startTime = currentTime;
	}

	// Mise à jour des objets
	Update();
	Render();

	// Limitation du framerate avec une synchronisation plus douce
	auto frameEndTime = std::chrono::steady_clock::now();
	std::chrono::duration<float> frameElapsed = frameEndTime - currentTime;
	float targetFrameTime = 1.0f / desiredFramerate;

	// Calcul du temps total �coul�
	std::chrono::duration<float> totalElapsed = currentTime - programStartTime;
	elapsedTotalSeconds = totalElapsed.count();

	// On accumule le temps restant au lieu d'un simple Sleep
	while (frameElapsed.count() < targetFrameTime) {
		frameEndTime = std::chrono::steady_clock::now();
		frameElapsed = frameEndTime - currentTime;
	}
}


void App::addObject()
{
	if (countBallList >= ballList.size())
		return; // Sort si toutes les balles ont été ajoutées

	static uint64_t lastTime = 0;
	uint64_t currentTime = GetTickCount64();

	// Si 1000 ms se sont écoulées, on ajoute une nouvelle balle
	if (currentTime - lastTime >= 1)
	{
		Ball ball;
		ball.Excute(ballList[countBallList]);
		ballManager->Init(ball);
		countBallList++;
		lastTime = currentTime;  // Met à jour le dernier temps
	}
}

void App::Update()
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	windowWidth = rect.right - rect.left;
	windowHeight = rect.bottom - rect.top;

	//On ajoute un objet
	addObject();
	//On met � jour les objets
	ballManager->Update(windowWidth, windowHeight);
}

void App::setDesiredFramerate(int framerate)
{
	desiredFramerate = framerate;
}

int App::getDesiredFramerate()
{
	return desiredFramerate;
}
