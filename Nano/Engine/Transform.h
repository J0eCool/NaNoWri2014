#pragma once

#include <SDL.h>

#include "Util/Util.h"
#include "Component.h"

class Transform : public Component {
public:
	Vec2 pos;
	Vec2 size;

	//$$pos:Vec2|size:Vec2
	void LoadArg(std::string const& key, std::string const& val) override;

	Vec2 GetCenter() const;
	SDL_Rect GetRect() const;
	SDL_Rect GetRectWithOffset(Vec2 const& offset) const;
};
