#pragma once

#include <map>
#include <initializer_list>
#include <typeinfo>

class Component;
class EntitySystem;
class Transform;

class Entity {
private:
	std::map<const std::type_info *, Component *> _components;
	EntitySystem *_entitySystem;

public:
	Entity();
	Entity(std::initializer_list<Component *> components);
	~Entity();

	template <typename T>
	T* AddComponent(T* component) {
		auto t = &typeid(T);
		if (!_components[t]) {
			_components[t] = component;
			_components[t]->_entity = this;
		}
		else {
			Log("Error: Adding component that already exists!");
		}
		return static_cast<T*>(_components[t]);
	}

	template <typename T>
	T* AddComponent() {
		return AddComponent(new T);
	}

	template <typename T>
	T* GetComponent() const {
		auto t = &typeid(T);
		auto it = _components.find(t);
		if (it != _components.end()) {
			return static_cast<T*>(it->second);
		}
		return nullptr;
	}

	Transform* GetTransform() const;

	inline EntitySystem* GetEntitySystem() const {
		return _entitySystem;
	}

	void Update(float dt);
	void Draw();

	friend EntitySystem;
};
