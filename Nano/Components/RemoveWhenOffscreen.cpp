#include "RemoveWhenOffscreen.h"

#include "Physics/Physics.h"

void RemoveWhenOffscreen::Start() {
	_camera = GetEntitySystem()->FindEntity("Camera");
}

void RemoveWhenOffscreen::Update(float dt) {
	auto collider = GetComponent<Collider>();
	auto collided = collider->GetCollidedEntities();
	if (collided.find(_camera) == collided.end()) {
		GetEntitySystem()->RemoveEntity(_entity);
	}
}
