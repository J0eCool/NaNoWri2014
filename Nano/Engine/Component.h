#pragma once

class Entity;

class Component {
protected:
	Entity *_entity;

	// TODO: restructure EntitySystem to use a "sea of components",
	// so component priority can actually work
	virtual float priority() { return 0.0f; }

public:
	// Called when Entity is added to EntitySystem
	virtual void Start() { };

	// Called every frame; logic is done here
	virtual void Update(float dt) { };

	// Called every frame; rendering is done here
	virtual void Draw() { };

	friend Entity;
};
