#include "pch.h"
#include "Move.h"

#include "Ball.h"



Move::Move()
{
}

Move::~Move()
{
}

void Move::ExcuteMove(Ball& ball)
{
	//Déplace la ball dans la direction donnée par rapport à la vitesse

	ball.setX(ball.getX() + ball.getSpeed() * ball.getDirectonX());
	ball.setY(ball.getY() + ball.getSpeed() * ball.getDirectonY());
}

void Move::ExcuteChangeDirection(Ball& ball, float windowWidth, float windowHeight)
{
	//Change la direction de la ball en fonction de la collision avec un coté de la fenêtre
	if (ball.getX() + ball.getSize() >= windowWidth || ball.getX() - ball.getSize() <= 0)
	{
		ball.setDirectonX(-ball.getDirectonX());
	}
	if (ball.getY() + ball.getSize() >= windowHeight || ball.getY() - ball.getSize() <= 0)
	{
		ball.setDirectonY(-ball.getDirectonY());
	}
}



