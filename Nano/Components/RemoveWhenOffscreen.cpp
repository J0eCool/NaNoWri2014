#include "RemoveWhenOffscreen.h"

#include "Physics/Physics.h"

RemoveWhenOffscreen::RemoveWhenOffscreen() : _remove(true) {
}

void RemoveWhenOffscreen::Start() {
	_camera = GetEntitySystem()->FindEntity("Camera");
}

void RemoveWhenOffscreen::Update(float dt) {
	auto collider = GetComponent<Collider>();
	auto collided = collider->GetCollidedEntities();
	_isOffscreen = collided.find(_camera) == collided.end();
	if (_isOffscreen) {
		if (_remove) {
			GetEntitySystem()->RemoveEntity(_entity);
		}
	}
}

bool RemoveWhenOffscreen::IsOffscreen() const {
	return _isOffscreen;
}