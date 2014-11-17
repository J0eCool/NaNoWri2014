#include "Bullet.h"

#include <Nano/Components/Physics/Physics.h>

void Bullet::Update(float dt) {
	Transform *transform = GetTransform();
	transform->pos += _vel * dt;

	Collider *collider = GetComponent<Collider>();
	auto collided = collider->GetCollidedEntities();
	if (collided.size() > 0) {
		bool shouldRemove = false;
		for (auto ent : collided) {
			if (!ent->GetComponent<Bullet>()) {
				ent->SendMessage("BulletHit");
				shouldRemove = true;
			}
		}
		if (shouldRemove) {
			GetEntitySystem()->RemoveEntity(_entity);
		}
	}
}

void Bullet::SetVel(Vec2 const& vel) {
	_vel = vel;
}
