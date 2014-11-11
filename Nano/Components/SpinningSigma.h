#pragma once

#include <Nano/Engine/Engine.h>

#include "Rendering/SpriteRenderer.h"

class SpinningSigma : public Component {
private:
	float _speed;
	float _color;
	float _t = 0.0f;

public:
	void Load(std::vector<std::string> const& args) override {
		float speed = ParseFloat(args[0]);
		float color = ParseFloat(args[1]);
		_speed = speed;
		_color = color;
	}

	void Update(float dt) override {
		SpriteRenderer *renderer = GetComponent<SpriteRenderer>();
		Sprite *sprite = renderer->GetSprite();
		sprite->angle += dt * _speed;
		_t += dt * _color;
		int c = lerp(sin(_t) / 2 + 0.5f, 0x00, 0xff);
		sprite->color = { 0xff, c, 0xff, 0xff };
	}
};
