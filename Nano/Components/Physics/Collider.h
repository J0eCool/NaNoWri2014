#pragma once

#include <Nano/Engine/Engine.h>

class Collider : public Component {
private:
	Vector<Entity *> _collidedThisFrame;
	int _layerMask;

protected:
	float priority() { return 10.0f; }
	bool collides(Collider *other);

public:
	Collider();
	//$$_layerMask:Int
	void LoadArg(String const& key, String const& val) override;

	void Update(float dt) override;

	Vector<Entity *> const& GetCollidedEntities() const;
	bool LayersIntersect(Collider *other) const;
	bool Raycast(Vec2 const& start, Vec2 const& end, float *outDist) const;
	bool IsPointInside(Vec2 point) const;
};
