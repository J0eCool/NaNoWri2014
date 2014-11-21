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
				ent->SendMessage("BulletHit", &_damage);
				shouldRemove = true;
			}
		}
		if (shouldRemove) {
			GetEntitySystem()->RemoveEntity(_entity);
			if (_container) {
				_container->_bullets.erase(this);
			}
		}
	}
}

void Bullet::SetDir(Vec2 const& dir) {
	_vel = dir * _speed;
}

void Bullet::setContainer(Container *container) {
	_container = container;
}

Bullet::Container::Container(int maxSize) : _maxSize(maxSize) {
}

bool Bullet::Container::IsFull() const {
	return _maxSize <= (int)_bullets.size();
}

void Bullet::Container::AddBullet(Bullet *bullet) {
	if (!IsFull()) {
		_bullets.insert(bullet);
		bullet->setContainer(this);
	}
}
