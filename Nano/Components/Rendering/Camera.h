#pragma once

#include <Nano/Engine/Engine.h>

class Camera : public Component {
private:
	Transform *_transform;

public:
	void Start() override;

	Vec2 GetOffset() const;
};
