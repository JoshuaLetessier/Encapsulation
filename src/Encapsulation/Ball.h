#pragma once

class Ball
{
public:
	Ball();
	virtual ~Ball();

	void Excute(ballStruct structure);

	float getSpeed();
	void setSpeed(float speed);

	float getX();
	void setX(float x);

	float getY();
	void setY(float y);

	float getCurrentTime();
	void setCurrentTime(float currentTime);

	float getLastTime();
	void setLastTime(float lastTime);

	float getSize();
	void setSize(float size);

	float getDirectonX();
	void setDirectonX(float directonX);

	float getDirectonY();
	void setDirectonY(float directonY);

	char* getTexture();

	bool operator==(const Ball& other) const {
		return (this->currentTime == other.currentTime);
	}

private:
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

