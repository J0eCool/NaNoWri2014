#pragma once

#include "Util/Util.h"

class Entity;
class EntitySystem;
class Transform;

class Component {
protected:
	Entity *_entity;

	// TODO: restructure EntitySystem to use a "sea of components",
	// so component priority can actually work
	virtual float priority() { return 0.0f; }

public:
	Component* SetArg(String const& key, String const& val) {
		LoadArg(key, val);
		return this;
	}
	virtual void LoadArg(String const& key, String const& val) { }

	// Called when Entity is added to EntitySystem; all components are loaded, other entities not necessarily
	virtual void Init() { }

	// Called before first Update call; can access other entites safely
	virtual void Start() { }

	// Called every frame; logic is done here
	virtual void Update(float dt) { }

	// Called every frame; rendering is done here
	virtual void Draw() { }

	virtual void HandleMessage(String const& message, void *data) { }

	template <typename T>
	T* GetComponent() {
		return _entity->GetComponent<T>();
	}

	Transform* GetTransform();
	EntitySystem* GetEntitySystem();

	friend Entity;
};
