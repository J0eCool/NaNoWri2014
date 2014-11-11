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
	void Update(float dt) override;

	std::vector<Entity *> const& GetCollidedEntities() const;
	bool Raycast(Vec2 const& start, Vec2 const& end, float *outDist) const;
	bool IsPointInside(Vec2 point) const;
};
