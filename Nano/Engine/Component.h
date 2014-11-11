#pragma once

#include <vector>
#include <string>

class Entity;

class Component {
protected:
	Entity *_entity;

	// TODO: restructure EntitySystem to use a "sea of components",
	// so component priority can actually work
	virtual float priority() { return 0.0f; }

public:
	// Called when Entity is loaded
	virtual void Load(std::vector<std::string> const& args) { }

	// Called when Entity is added to EntitySystem
	virtual void Start() { }

	// Called every frame; logic is done here
	virtual void Update(float dt) { }

	// Called every frame; rendering is done here
	virtual void Draw() { }

	template <typename T>
	T* GetComponent() {
		return _entity->GetComponent<T>();
	}

	friend Entity;
};
