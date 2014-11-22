#pragma once

#include "Util/Util.h"

#include <Nano/Generated/ComponentEnums.h>

class Entity;
class EntitySystem;
class Transform;

class Component {
private:
	ComponentType _type;

protected:
	Entity *_entity;

	// TODO: restructure EntitySystem to use a "sea of components",
	// so component priority can actually work
	virtual float priority() { return 0.0f; }

public:
	virtual ~Component() { }

	Component* SetArg(String const& key, String const& val) {
		LoadArg(key, val);
		return this;
	}
	virtual void LoadArg(String const& key, String const& val) { }

	// Called when Entity is added to EntitySystem; all components are loaded, other entities not necessarily
	virtual void Init() { }

	// Called when Entity is removed from EntitySystem
	virtual void Deinit() { }

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
	friend Component* ParseComponent(Vector<String>& lines);
};
