#include "pch.h"
#include "Ball.h"

Ball::Ball()
{
}

Ball::~Ball()
{
	texture[0] = '\0';
}

void Ball::Excute(ballStruct structure)
{
	speed = structure.speed;
	x = structure.x;
	y = structure.y;
	currentTime = structure.currentTime;
	lastTime = structure.lastTime;
	size = structure.size;
	directonX = structure.directonX;
	directonY = structure.directonY;
	strcpy_s(texture, structure.texture);
	texture[sizeof(texture) - 1] = '\0';
}

float Ball::getSpeed()
{
	return speed;
}

void Ball::setSpeed(float speed)
{
	this->speed = speed;
}

float Ball::getX()
{
	return x;
}

void Ball::setX(float x)
{
	this->x = x;
}

float Ball::getY()
{
	return y;
}

void Ball::setY(float y)
{
	this->y = y;
}

float Ball::getCurrentTime()
{
	return currentTime;
}

void Ball::setCurrentTime(float currentTime)
{
	this->currentTime = currentTime;

}

float Ball::getLastTime()
{
	return lastTime;
}

void Ball::setLastTime(float lastTime)
{
	this->lastTime = lastTime;
}

float Ball::getSize()
{
	return size;
}

void Ball::setSize(float size)
{
	this->size = size;
}

float Ball::getDirectonX()
{
	return directonX;
}

void Ball::setDirectonX(float directonX)
{
	this->directonX = directonX;
}

float Ball::getDirectonY()
{
	return directonY;
}

void Ball::setDirectonY(float directonY)
{
	this->directonY = directonY;
}

char* Ball::getTexture()
{
	return texture;
}