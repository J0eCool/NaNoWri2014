#include "Rigidbody.h"

#include "Collider.h"

Rigidbody::Rigidbody() : _penetrationResistance(100.0f), _xPoints(1), _yPoints(1) {
}

void Rigidbody::Update(float dt) {
	auto collided = GetComponent<Collider>()->GetCollidedEntities();
	if (collided.size() > 0) {
		Transform *transform = _entity->GetTransform();
		Collider *collider = GetComponent<Collider>();
		Vec2 center(transform->GetCenter());
		Vec2 halfSize(transform->size / 2.0f);

		//float dist;
		//float h2 = transform->size.y / 2.0f;
		//if (collider->Raycast(center, center + Vec2(0.0f, h2), &dist)) {
		//	transform->pos.y -= h2 - dist;
		//}

		float dist;
		for (int i = 0; i < _xPoints + 2; ++i) {
			Vec2 p;
			p.x = transform->pos.x + transform->size.x * i / (_xPoints + 1);
			p.y = center.y;
			if (collider->Raycast(p, p + Vec2(0.0f, halfSize.y), &dist)) {
				transform->pos.y -= halfSize.y - dist;
			}
			if (collider->Raycast(p, p - Vec2(0.0f, halfSize.y), &dist)) {
				transform->pos.y += halfSize.y - dist;
			}
		}
		for (int i = 0; i < _yPoints + 2; ++i) {
			Vec2 p;
			p.x = center.x;
			p.y = transform->pos.y + transform->size.y * i / (_yPoints + 1);
			if (collider->Raycast(p, p + Vec2(halfSize.x, 0.0f), &dist)) {
				transform->pos.x -= halfSize.x - dist;
			}
			if (collider->Raycast(p, p - Vec2(halfSize.x, 0.0f), &dist)) {
				transform->pos.x += halfSize.x - dist;
			}
		}

		//int nPoints = 2 * (_xPoints + _yPoints + 4);
		//Vec2 delta;
		//for (auto colEntity : collided) {
		//	Transform *colTransform = colEntity->GetTransform();
		//	Vec2 d = colTransform->GetCenter() - center;
		//	if (d.x < d.y) {
		//		delta.x = absMax(delta.x, d.x);
		//	}
		//	else {
		//		delta.y = absMax(delta.y, d.y);
		//	}
		//}
		//transform->pos -= delta;
	}
}
