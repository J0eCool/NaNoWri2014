#pragma once

class Entity;

class Component {
protected:
	Entity *_entity;

public:
	virtual void Update(float dt) { };
	virtual void Draw() { };

	friend Entity;
};
