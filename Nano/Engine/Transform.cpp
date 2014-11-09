#include "Transform.h"

#include "Util/Util.h"

Transform::Transform() {
}

Transform::Transform(Vec2 _pos, Vec2 _size) {
	Init(_pos, _size);
}

void Transform::Load(std::vector<std::string> const& args) {
	pos.x = ParseFloat(args[0]);
	pos.y = ParseFloat(args[1]);
	size.x = ParseFloat(args[2]);
	size.y = ParseFloat(args[3]);
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
