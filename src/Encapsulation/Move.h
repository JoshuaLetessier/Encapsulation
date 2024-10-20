#pragma once

#include "Ball.h"

class Move
{
public:
	Move();
	virtual ~Move();

	void ExcuteMove(Ball& ball);
	void ExcuteChangeDirection(Ball& ball, float windowWidth, float windowHeight);
};

