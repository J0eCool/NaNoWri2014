#include "Rigidbody.h"

#include "Collider.h"

Rigidbody::Rigidbody() : _penetrationResistance(100.0f), _xPoints(1), _yPoints(1) {
}

void Rigidbody::Update(float dt) {
	//auto collided = GetComponent<Collider>()->GetCollidedEntities();
	//if (collided.size() > 0) {
		Transform *transform = _entity->GetTransform();
		transform->pos += vel * dt;
		Collider *collider = GetComponent<Collider>();
		Vec2 halfSize(transform->size / 2.0f);

		float dist;
		for (int i = 0; i < _xPoints + 2; ++i) {
			Vec2 p;
			p.x = transform->pos.x + (transform->size.x - 0.1f) * i / (_xPoints + 1);
			p.y = transform->GetCenter().y;
			if (collider->Raycast(p, p + Vec2(0.0f, halfSize.y), &dist)) {
				transform->pos.y -= halfSize.y - dist;
				p.y -= halfSize.y - dist;
			}
			if (collider->Raycast(p, p - Vec2(0.0f, halfSize.y), &dist)) {
				transform->pos.y += halfSize.y - dist;
				p.y += halfSize.y - dist;
			}
		}
		for (int i = 0; i < _yPoints + 2; ++i) {
			Vec2 p;
			p.x = transform->GetCenter().x;
			p.y = transform->pos.y + (transform->size.y - 0.1f) * i / (_yPoints + 1);
			if (collider->Raycast(p, p + Vec2(halfSize.x, 0.0f), &dist)) {
				transform->pos.x -= halfSize.x - dist;
				p.x -= halfSize.x - dist;
			}
			if (collider->Raycast(p, p - Vec2(halfSize.x, 0.0f), &dist)) {
				transform->pos.x += halfSize.x - dist;
				p.x += halfSize.x - dist;
			}
		}
	//}
}
