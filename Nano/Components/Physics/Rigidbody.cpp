#include "Rigidbody.h"

#include "Collider.h"

const float Rigidbody::kGravity = 2500.0f;

Rigidbody::Rigidbody() : _xPoints(1), _yPoints(1), _layerMask(Collider::kDefaultLayerMask) {
}

struct RayPointData {
	Vec2 pos;
	Vec2 dir;
	CollisionDirection colDir;
};

void Rigidbody::Update(float dt) {
	Transform *transform = _entity->GetTransform();
	Vec2 v = vel * dt;

	Vector<RayPointData> rays;
	float eps = 0.01f;
	for (int i = 0; i < _xPoints + 2; i++) {
		float x = transform->pos.x + eps + (transform->size.x - 2 * eps) * i / (_xPoints + 1);
		if (v.y <= 0.0f) {
			rays.push_back({ { x, transform->pos.y }, { 0.0f, v.y }, CD_Up });
		}
		if (v.y >= 0.0f) {
			CollisionDirection dir = CD_Down;
			if (i == 0) {
				dir = (CollisionDirection)(dir | CD_DownLeftSide);
			}
			else if (i == _xPoints + 1) {
				dir = (CollisionDirection)(dir | CD_DownRightSide);
			}
			rays.push_back({ { x, transform->pos.y + transform->size.y }, { 0.0f, v.y }, dir });
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
		float dist = FLT_MAX;
		if (collider->Raycast(r.pos, r.pos + r.dir, &dist, _layerMask)) {
			_collidedDirs = (CollisionDirection)(_collidedDirs | r.colDir);
			if (r.colDir & CD_Horizontal) {
				v.x = absMin(v.x, dist * sign1(v.x));
			}
			else {
				v.y = absMin(v.y, dist * sign1(v.y));
			}
		}
	}

	if (_collidedDirs & CD_Vertical) {
		vel.y = 0.0f;
	}
	if (!(_collidedDirs & CD_Down)) {
		vel.y += kGravity * dt;
	}

	transform->pos += v;
}

bool Rigidbody::IsColliding(CollisionDirection dir) const {
	return (_collidedDirs & dir) != 0;
}
