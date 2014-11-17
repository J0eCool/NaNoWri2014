#pragma once

#include <SDL.h>
#include <string>

#include <Nano/Engine/Engine.h>

#include <Nano/Sprite.h>

class Camera;

class SpriteRenderer : public Component {
private:
	Sprite _sprite;
	std::string _spriteName;
	Camera *_camera;

public:
	//$$_spriteName:String
	void LoadArg(std::string const& key, std::string const& val) override;

	void Start() override;
	void Draw() override;

	Sprite* GetSprite();
};