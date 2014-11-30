#pragma once

#include <Nano/Engine/Engine.h>
#include <Nano/Sprite.h>

#include <functional>

typedef std::function<int()> HealthFunc;

class HealthBar : public Component {
private:
	SDL_Color _color;
	Sprite _segment;
	Sprite _endcap;

	HealthFunc _curFunc;
	HealthFunc _maxFunc;

protected:
	float priority() const override { return 10.0f; }

public:
	//$$_color:Color
	void LoadArg(String const& key, String const& val) override;
	void Init() override;
	void Draw() override;

	void SetFunctions(HealthFunc cur, HealthFunc max);
};
