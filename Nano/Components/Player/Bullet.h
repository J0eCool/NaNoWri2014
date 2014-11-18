#pragma once

#include <Nano/Engine/Engine.h>

class Bullet : public Component {
private:
	Vec2 _vel;

public:
	//$$_vel:Vec2
	void LoadArg(String const& key, String const& val) override;

	void Update(float dt) override;

	void SetVel(Vec2 const& vel);
};
