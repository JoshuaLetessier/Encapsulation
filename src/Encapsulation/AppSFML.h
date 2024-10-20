#pragma once
#ifdef _SFML

#include "App.h"

#include "WindowSFML.h"
#include "GraphicSFML.h"


class AppSFML :
    public App
{
public:
	AppSFML();
	virtual ~AppSFML();

	void Init(HINSTANCE hInstance, int nCmdShow) override;
	void Render() override;
	void RenderObject() override;
	void RenderDebugInfo() override;

	WindowSFML* getWindow();

private:
	WindowSFML* window;
	GraphicSFML* graphics;
};

#endif // _SFML