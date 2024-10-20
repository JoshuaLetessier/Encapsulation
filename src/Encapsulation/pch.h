#pragma once

#ifdef _SFML
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#endif // 

#include <windows.h>

#pragma comment(lib, "Msimg32.lib")

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <unordered_map>

#include "resource.h"

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DEBUG_NEW
#endif

struct  ballStruct
{
	float speed;
	float x;
	float y;
	float currentTime;
	float lastTime;
	float size;
	float directonX;
	float directonY;
	char texture[100];

};