#pragma once

#include <Nano/Engine/Engine.h>

class CameraFollow : public Component {
private:
	std::string _followName;
	Transform* _followTransform;

public:
	void Load(std::vector<std::string> const& args) override;
	void Start() override;
	void Update(float dt) override;
};
