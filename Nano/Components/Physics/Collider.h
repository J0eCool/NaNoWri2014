#pragma once

#include <Nano/Engine/Engine.h>

#include <string>
#include <vector>

class Collider : public Component {
private:
	std::vector<Entity *> _collidedThisFrame;
	int _layerMask;

protected:
	float priority() { return 10.0f; }
	bool collides(Collider *other);

public:
	Collider();
	//$$_layerMask:Int
	void LoadArg(std::string const& key, std::string const& val) override;

	void Update(float dt) override;

	std::vector<Entity *> const& GetCollidedEntities() const;
	bool LayersIntersect(Collider *other) const;
	bool Raycast(Vec2 const& start, Vec2 const& end, float *outDist) const;
	bool IsPointInside(Vec2 point) const;
};
