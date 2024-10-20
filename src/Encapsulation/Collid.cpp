#include "pch.h"
#include "Collid.h"

#include "Ball.h"

Collid::Collid()
{
}

Collid::~Collid()
{
}

bool Collid::Excute(Ball& ball, int windowWidth, int windowHeight)
{
	//Test si la ball est en collision avec un cot� de la fen�tre
	if (ball.getX() + ball.getSize() >= windowWidth || ball.getX() - ball.getSize() <= 0)
	{
		return true;
	}
	if (ball.getY() + ball.getSize() >= windowHeight || ball.getY() - ball.getSize() <= 0)
	{
		return true;
	}
	return false;
}
