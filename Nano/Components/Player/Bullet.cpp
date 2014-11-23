#include "Bullet.h"

#include <Nano/Components/Physics/Physics.h>

void Bullet::Deinit() {
	if (_container) {
		_container->_bullets.erase(this);
	}
}

void Bullet::Update(float dt) {
	Transform *transform = GetTransform();
	transform->pos += _vel * dt;

	Collider *collider = GetComponent<Collider>();
	auto collided = collider->GetCollidedEntities();
	if (collided.size() > 0) {
		bool shouldRemove = false;
		for (auto ent : collided) {
			auto oCol = ent->GetComponent<Collider>();
			if (!ent->GetComponent<Bullet>() && collider->LayersIntersect(oCol, _layerMask)) {
				ent->SendMessage("BulletHit", &_damage);
				shouldRemove = true;
			}
		}
		if (shouldRemove) {
			GetEntitySystem()->RemoveEntity(_entity);
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

Bullet::Container::~Container() {
	for (auto bullet : _bullets) {
		bullet->setContainer(nullptr);
	}
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
