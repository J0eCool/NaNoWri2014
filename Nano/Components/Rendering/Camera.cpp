#include "Camera.h"

void Camera::Start() {
}

Vec2 Camera::GetOffset() const {
	return -_transform->pos;
}
