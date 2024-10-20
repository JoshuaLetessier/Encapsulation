#include "pch.h"
#include "BallManager.h"

#include "Ball.h"
#include "Graphic.h"



BallManager::BallManager()
{
}

BallManager::~BallManager()
{
}

void BallManager::Init(Ball ball)
{
	std::cout << "Init" << std::endl;
	balls.push_back(ball);
}

void BallManager::Update(float windowWidth, float windowHeight)
{
	std::vector<Ball>::iterator it = balls.begin();
	while (it != balls.end())
	{
		//Si la ball a atteint son temps max, on la supprime
		if (!IsMaxTime(*it))
		{
			it = balls.erase(it);
		}
		else
		{
			//Update la ball
			//test si la ball est en collision avec un autre objet
			//Si oui, on applique un changement de direction
			if (collid->Excute(*it, windowWidth, windowHeight))
			{
				move->ExcuteChangeDirection(*it, windowWidth, windowHeight);
				move->ExcuteMove(*it);
			}
			//Si non, on la d�place normalement
			else
			{
				move->ExcuteMove(*it);
			}
			it->setCurrentTime(it->getCurrentTime() + 1);
			++it;
		}
	}
}

bool BallManager::IsMaxTime(Ball& ball)
{
	if (ball.getCurrentTime() >= ball.getLastTime())
		return false;
    return true;
}

std::vector<Ball>& BallManager::getBalls()
{
    return balls;
}
