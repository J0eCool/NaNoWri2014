#include "Camera.h"

void Camera::Start() {
	_transform = GetComponent<Transform>();
}

Vec2 Camera::GetOffset() const {
	return -_transform->pos;
}
