#pragma once

class Entity;

class Component {
protected:
	Entity *_entity;

	// TODO: restructure EntitySystem to use a "sea of components",
	// so component priority can actually work
	virtual float priority() { return 0.0f; }

public:
	virtual void Update(float dt) { };
	virtual void Draw() { };

	friend Entity;
};
