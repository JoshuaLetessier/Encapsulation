#pragma once
#include <vector>
#include "Move.h"
#include "Collid.h"

class BallManager
{
public :
	BallManager();
	virtual ~BallManager();

	void Init(Ball ball);
	void Update(float windowWidth, float windowHeight);

	bool IsMaxTime(Ball& ball);

public: //getter
	std::vector<Ball>& getBalls();

private:
	std::vector<Ball> balls;

	Move* move;
	Collid* collid;
};

