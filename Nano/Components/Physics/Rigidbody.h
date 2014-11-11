#pragma once

#include <Nano/Engine/Engine.h>

class Rigidbody : public Component {
private:
	float _penetrationResistance;
	int _xPoints;
	int _yPoints;

public:
	Rigidbody();

	void Update(float dt) override;
};
