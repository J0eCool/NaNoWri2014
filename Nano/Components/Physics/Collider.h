#pragma once

#include <Nano/Engine/Engine.h>

class Collider : public Component {
private:
	Vector<Entity *> _collidedThisFrame;
	int _layerMask;

protected:
	float priority() const override { return -10.0f; }
	bool collides(Collider *other);

public:
	const static int kDefaultLayerMask = 0x1;

	Collider();
	//$$_layerMask:Int
	void LoadArg(String const& key, String const& val) override;

	void Update(float dt) override;

	Vector<Entity *> const& GetCollidedEntities() const;
	bool LayersIntersect(Collider *other, int layerMask = -1) const;
	bool Raycast(Vec2 const& start, Vec2 const& end, float *outDist, int layerMask = -1) const;
	bool IsPointInside(Vec2 point) const;
};
