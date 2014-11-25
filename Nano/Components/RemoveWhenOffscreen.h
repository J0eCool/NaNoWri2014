#pragma once

#include <Nano/Engine/Engine.h>

class RemoveWhenOffscreen : public Component {
private:
	bool _remove;

	Entity *_camera;
	bool _isOffscreen;

protected:
	float priority() const override { return -1.0f; }

public:
	RemoveWhenOffscreen();
	//$$_remove:Bool
	void LoadArg(String const& key, String const& val);

	void Start() override;
	void Update(float dt) override;

	bool IsOffscreen() const;
};
