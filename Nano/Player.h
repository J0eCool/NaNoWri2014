#pragma once

#include "Vec2.h"

class Player {
private:
	Vec2 pos;

public:
	Player();

	void Update();
	void Draw();
};

