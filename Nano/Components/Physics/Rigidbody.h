#pragma once

#include <Nano/Engine/Engine.h>

enum CollisionDirection {
	CD_Left = 1 << 0,
	CD_Right = 1 << 1,
	CD_Down = 1 << 2,
	CD_Up = 1 << 3,

	CD_None = 0,
	CD_Horizontal = CD_Left | CD_Right,
	CD_Vertical = CD_Down | CD_Up,
};

class Rigidbody : public Component {
private:
	int _xPoints;
	int _yPoints;
	CollisionDirection _collidedDirs;
	int _layerMask;

protected:
	float priority() const override { return -5.0f; }

public:
	const static float kGravity;

	//$$_layerMask:Int
	void LoadArg(String const& key, String const& val) override;

	Vec2 vel;
	Rigidbody();

	void Update(float dt) override;

	CollisionDirection GetCollisionDirs() const;
};
