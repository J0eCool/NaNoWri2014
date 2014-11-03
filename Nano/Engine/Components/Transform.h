#pragma once

#include <SDL.h>
#include "../Component.h"
#include "../../Util/Vec2.h"

class Transform : public Component {
public:
	Vec2 size;
	Vec2 pos;

	void Init(Vec2 _size, Vec2 _pos);

	SDL_Rect GetRect() const;
};
