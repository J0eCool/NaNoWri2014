#pragma once

#include <Nano/Engine/Engine.h>

class RemoveWhenOffscreen : public Component {
private:
	Entity *_camera;

public:
	void Start() override;
	void Update(float dt) override;
};
