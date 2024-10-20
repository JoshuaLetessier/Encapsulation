#pragma once

class Ball;

class Collid
{
public:
	Collid();
	virtual ~Collid();
	
	bool Excute(Ball& ball, int windowWidth, int windowHeight);
};

