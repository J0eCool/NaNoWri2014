#pragma once

#include <Nano/Engine/Engine.h>

enum BossState {
	BS_NONE,

	BS_Start,
	BS_Hop,
	BS_Dash,
	BS_Jump,
};

class Boss : public Component {
private:
	BossState _state;
	int _dir;

	float _timer;
	int _counter;

public:
	Boss();
	void Start() override;
	void Deinit() override;
	void Update(float dt) override;
};
