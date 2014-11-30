#pragma once

#include <Nano/Engine/Engine.h>

class Boss : public Component {
public:
	void Start() override;
	void Deinit() override;
};
