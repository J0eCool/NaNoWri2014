#pragma once

#include "Util/Util.h"

#include <initializer_list>
#include <typeinfo>

class Component;
class EntitySystem;
class Transform;

#include <Nano/Generated/ComponentEnums.h>

class Entity {
private:
	Vector<Component *> _components;
	EntitySystem *_entitySystem;
	String _name;

	template <typename F>
	inline void forAllComponents(F func) {
		for (auto cmp : _components) {
			if (cmp) {
				func(cmp);
			}
		}
	}

public:
	Entity(String name);
	Entity(Entity const& other);
	~Entity();

	Component* AddComponent(Component* component);

	template <typename T>
	inline T* GetComponent() {
		ComponentType type = GetComponentType(&typeid(T));
		return static_cast<T*>(_components[type]);
	}

	Transform* GetTransform();

	inline EntitySystem* GetEntitySystem() const {
		return _entitySystem;
	}

	void SendMessage(String const& message, void *data = nullptr);

	friend EntitySystem;
};
