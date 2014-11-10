#include "Collider.h"

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
		if (entity != _entity && col && collides(col)) {
			_collidedThisFrame.push_back(entity);
		}
	}
}

std::vector<Entity *> const& Collider::GetCollidedEntities() const {
	return _collidedThisFrame;
}
