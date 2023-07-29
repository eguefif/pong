#pragma once
#include "def.h"
#include "ball.h"

class IA
{
public:
	IA() = default;
	enum direction {
		UP = 1,
		DOWN = 2,
		FREEZE = 0
	};
	int where_to_go(Ball ball, Racket racket);

private:
};
