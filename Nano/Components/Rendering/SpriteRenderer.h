#pragma once

#include <SDL.h>
#include <string>

#include <Nano/Engine/Engine.h>

#include <Nano/Sprite.h>

class SpriteRenderer : public Component {
private:
	Sprite _sprite;
	std::string _spriteName;

public:
	void Load(std::vector<std::string> const& args) override;

	void Start() override;
	void Draw() override;

	Sprite* GetSprite();
};