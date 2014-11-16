#pragma once

#include <SDL.h>

#include "Util/Util.h"
#include "Component.h"

class Transform : public Component {
public:
	Vec2 pos;
	Vec2 size;

	void Load(std::vector<std::string> const& args) override;

	Vec2 GetCenter() const;
	SDL_Rect GetRect() const;
	SDL_Rect GetRectWithOffset(Vec2 const& offset) const;
};
