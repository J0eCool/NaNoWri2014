#pragma once

#include <map>
#include <typeinfo>

class Component;

class Entity {
private:
	std::map<const std::type_info *, Component *> _components;

public:
	~Entity();

	template <typename T>
	T* AddComponent() {
		auto t = &typeid(T);
		if (!_components[t]) {
			_components[t] = new T;
			_components[t]->_entity = this;
		}
		else {
			Log("Error: Adding component that already exists!");
		}
		return static_cast<T*>(_components[t]);
	}

	template <typename T>
	T* GetComponent() {
		auto t = &typeid(T);
		return static_cast<T*>(_components[t]);
	}

	void Update(float dt);
	void Draw();
};
