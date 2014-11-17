#include "Collider.h"

Collider::Collider() : _layerMask(0xffff) {
}

bool Collider::collides(Collider *other) {
	Transform *a = _entity->GetTransform();
	Transform *b = other->_entity->GetTransform();

	float xA = a->pos.x;
	float xB = a->pos.x + a->size.x;
	float xC = b->pos.x;
	float xD = b->pos.x + b->size.x;

	float yA = a->pos.y;
	float yB = a->pos.y + a->size.y;
	float yC = b->pos.y;
	float yD = b->pos.y + b->size.y;

	// Separating Axis Theorem
	return
		// x-axis
		(xA >= xC && xA <= xD ||
		xB >= xC && xB <= xD ||
		xC >= xA && xC <= xB ||
		xD >= xA && xD <= xB)
	&&
		// y-axis
		(yA >= yC && yA <= yD ||
		yB >= yC && yB <= yD ||
		yC >= yA && yC <= yB ||
		yD >= yA && yD <= yB)
	;
}

void Collider::Update(float dt) {
	_collidedThisFrame.clear();

	auto entities = _entity->GetEntitySystem()->GetEntities();
	for (auto entity : entities) {
		Collider *col = entity->GetComponent<Collider>();
		if (entity != _entity && col && LayersIntersect(col) && collides(col)) {
			_collidedThisFrame.push_back(entity);
		}
	}
}

std::vector<Entity *> const& Collider::GetCollidedEntities() const {
	return _collidedThisFrame;
}

bool lineIntersects(Vec2 const& a1, Vec2 const& a2,
		Vec2 const& b1, Vec2 const& b2, float *outDist) {
	Vec2 da(a2 - a1);
	Vec2 db(b2 - b1);
	float t = (b1 - a1).Cross(db) / da.Cross(db);
	float u = (a1 - b1).Cross(da) / db.Cross(da);
	if (t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f) {
		if (outDist) {
			*outDist = t * da.Length();
		}
		return true;
	}
	return false;
}

bool Collider::LayersIntersect(Collider *other) const {
	return (other->_layerMask & _layerMask) != 0;
}

bool Collider::Raycast(Vec2 const& start, Vec2 const& end, float *outDist) const {
	bool collided = false;
	float dist = FLT_MAX;
	auto entities = _entity->GetEntitySystem()->GetEntities();
	for (auto entity : entities) {
		Collider *col = entity->GetComponent<Collider>();
		if (col && entity != _entity && LayersIntersect(col)) {
			if (col->IsPointInside(start)) {
				if (outDist) {
					*outDist = 0.0f;
				}
				return true;
			}
			Transform *t = entity->GetTransform();
			Vec2 points[] = {
				t->pos,
				Vec2(t->pos.x, t->pos.y + t->size.y),
				t->pos + t->size,
				Vec2(t->pos.x + t->size.x, t->pos.y),
			};
			for (int i = 0; i < 4; i++) {
				Vec2 *a = points + i;
				Vec2 *b = points + (i + 1) % 4;
				float out = FLT_MAX;
				if (lineIntersects(start, end, *a, *b, &out)) {
					collided = true;
					dist = min(dist, out);
				}
			}
		}
	}
	if (outDist) {
		*outDist = dist;
	}
	return collided;
}

bool Collider::IsPointInside(Vec2 point) const {
	Transform *transform = _entity->GetTransform();
	SDL_Rect r = transform->GetRect();
	return point.x >= r.x && point.x <= r.x + r.w &&
		point.y >= r.y && point.y <= r.y + r.h;
}
