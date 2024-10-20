#pragma once

#include "Ball.h"

class Graphic
{
public: 
	Graphic();
	virtual ~Graphic();
	
	virtual void init(HWND hwnd);
	virtual void draw(Ball* ball);
	virtual void loadTexture(Ball* ball);
	virtual void removeTexture(Ball* ball) = 0;
	virtual void display();
	virtual void clear();

protected:
	virtual bool isBMP24Bits(std::string texturePath);
};

