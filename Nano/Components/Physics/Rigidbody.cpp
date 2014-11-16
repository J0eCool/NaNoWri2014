#include "Rigidbody.h"

#include "Collider.h"

Rigidbody::Rigidbody() : _penetrationResistance(100.0f), _xPoints(1), _yPoints(1) {
}

struct RayPointData {
	Vec2 pos;
	Vec2 dir;
	CollisionDirection colDir;
};

void Rigidbody::Update(float dt) {
	Transform *transform = _entity->GetTransform();
	Vec2 v = vel * dt;

	std::vector<RayPointData> rays;
	float eps = 0.01f;
	for (int i = 0; i < _xPoints + 2; i++) {
		float x = transform->pos.x + eps + (transform->size.x - 2 * eps) * i / (_xPoints + 1);
		if (v.y <= 0.0f) {
			rays.push_back({ { x, transform->pos.y }, { 0.0f, v.y }, CD_Up });
		}
		if (v.y >= 0.0f) {
			rays.push_back({ { x, transform->pos.y + transform->size.y }, { 0.0f, v.y }, CD_Down });
		}
	}
	for (int i = 0; i < _yPoints + 2; i++) {
		float y = transform->pos.y + eps + (transform->size.y - 2 * eps) * i / (_yPoints + 1);
		if (v.x <= 0.0f) {
			rays.push_back({ { transform->pos.x, y }, { v.x, 0.0f }, CD_Left });
		}
		if (v.x >= 0.0f) {
			rays.push_back({ { transform->pos.x + transform->size.x, y }, { v.x, 0.0f }, CD_Right });
		}
	}

	Collider *collider = GetComponent<Collider>();
	_collidedDirs = CD_None;
	static int frame = 0;
	frame++;
	for (auto r : rays) {
		float dist = 0.0f;
		if (collider->Raycast(r.pos, r.pos + r.dir, &dist)) {
			_collidedDirs = (CollisionDirection)(_collidedDirs | r.colDir);
			if (r.colDir & CD_Horizontal) {
				v.x = absMin(v.x, dist);
			}
			else {
				v.y = absMin(v.y, dist);
			}
		}
	}

	transform->pos += v;
}

CollisionDirection Rigidbody::GetCollisionDirs() const {
	return _collidedDirs;
}
