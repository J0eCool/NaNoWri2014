#pragma once

#include <vector>

#include <Nano/Engine/Engine.h>

class Collider : public Component {
private:
	std::vector<Entity *> _collidedThisFrame;

protected:
	float priority() { return 10.0f; }
	bool collides(Collider *other);

public:
	Collider() {};

	void Update(float dt);

	std::vector<Entity *> const& GetCollidedEntities() const;
};
