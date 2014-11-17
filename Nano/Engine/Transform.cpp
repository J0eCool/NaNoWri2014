#include "Transform.h"

#include "Util/Util.h"

Vec2 Transform::GetCenter() const {
	return Vec2(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f);
}

SDL_Rect Transform::GetRect() const {
	SDL_Rect rect;
	rect.x = (int)pos.x;
	rect.y = (int)pos.y;
	rect.w = (int)size.x;
	rect.h = (int)size.y;
	return rect;
}

SDL_Rect Transform::GetRectWithOffset(Vec2 const& offset) const {
	SDL_Rect rect;
	rect.x = (int)(pos.x + offset.x);
	rect.y = (int)(pos.y + offset.y);
	rect.w = (int)size.x;
	rect.h = (int)size.y;
	return rect;
}
