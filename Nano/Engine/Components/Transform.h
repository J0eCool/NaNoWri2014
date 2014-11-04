#pragma once

#include <SDL.h>
#include "../Component.h"
#include "../../Util/Vec2.h"

class Transform : public Component {
public:
	Vec2 pos;
	Vec2 size;

	void Init(Vec2 _pos, Vec2 _size);

	SDL_Rect GetRect() const;
};
