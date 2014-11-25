#pragma once

#include <Nano/Engine/Engine.h>

class Collider : public Component {
private:
	Set<Entity *> _collidedThisFrame;
	int _layerMask;

protected:
	float priority() const override { return -10.0f; }
	bool collides(Collider *other);

public:
	const static int kDefaultLayerMask = 0x1;

	Collider();
	Component* Clone() const override;
	//$$_layerMask:Int
	void LoadArg(String const& key, String const& val) override;

	void Update(float dt) override;

	Set<Entity *> const& GetCollidedEntities() const;
	bool LayersIntersect(Collider *other, int layerMask = -1) const;
	bool Raycast(Vec2 const& start, Vec2 const& end, float *outDist, int layerMask = -1) const;
	bool IsPointInside(Vec2 point) const;
};
