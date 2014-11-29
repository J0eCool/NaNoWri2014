#pragma once

#include <Nano/Engine/Engine.h>

class EnemyWander : public Component {
private:
	float _speed;
	int _dir;

public:
	EnemyWander();
	//$$_speed:Float|_dir:Int
	void LoadArg(String const& key, String const& val) override;
	void Update(float dt) override;
};
