#include "Transform.h"

Transform::Transform() {
}

Transform::Transform(Vec2 _pos, Vec2 _size) {
	Init(_pos, _size);
}

void Transform::Init(Vec2 _pos, Vec2 _size) {
	pos = _pos;
	size = _size;
}

SDL_Rect Transform::GetRect() const {
	SDL_Rect rect;
	rect.x = (int)pos.x;
	rect.y = (int)pos.y;
	rect.w = (int)size.x;
	rect.h = (int)size.y;
	return rect;
}
