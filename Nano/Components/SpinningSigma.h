#pragma once

#include <Nano/Engine/Engine.h>

#include "Rendering/SpriteRenderer.h"

class SpinningSigma : public Component {
private:
	float _speed;
	float _color;
	float _t = 0.0f;

public:
	SpinningSigma() {}
	SpinningSigma(float speed, float color) { Init(speed, color); }
	void Init(float speed, float color) {
		_speed = speed;
		_color = color;
	}

	void Update(float dt) override {
		SpriteRenderer *renderer = _entity->GetComponent<SpriteRenderer>();
		Sprite *sprite = renderer->GetSprite();
		sprite->angle += dt * _speed;
		_t += dt * _color;
		int c = lerp(sin(_t) / 2 + 0.5f, 0x00, 0xff);
		sprite->color = { 0xff, c, 0xff, 0xff };
	}
};
