#pragma once

#include <SDL.h>
#include <string>

#include <Nano/Engine/Engine.h>

#include <Nano/Sprite.h>

class Camera;

class SpriteRenderer : public Component {
private:
	Sprite _sprite;
	String _spriteName;
	Camera *_camera;

public:
	//$$_spriteName:String
	void LoadArg(String const& key, String const& val) override;

	void Init() override;
	void Start() override;
	void Draw() override;

	Sprite* GetSprite();
};