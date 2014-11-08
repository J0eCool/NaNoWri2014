#pragma once

#include <SDL.h>

#include "Util/Util.h"
#include "Component.h"

class Transform : public Component {
public:
	Vec2 pos;
	Vec2 size;

	Transform();
	Transform(Vec2 _pos, Vec2 _size);

	void Init(Vec2 _pos, Vec2 _size);

	SDL_Rect GetRect() const;
};
