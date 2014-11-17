#pragma once

#include <map>
#include <initializer_list>
#include <typeinfo>

class Component;
class EntitySystem;
class Transform;

#include <Nano/Generated/ComponentEnums.h>

class Entity {
private:
	std::map<ComponentType, Component *> _components;
	EntitySystem *_entitySystem;
	std::string _name;
	bool _hasStarted = false;

public:
	Entity(std::string name);
	~Entity();

	Component* AddComponent(ComponentType type, Component* component);

	template <typename T>
	T* GetComponent() {
		ComponentType type = GetComponentType(&typeid(T));
		auto it = _components.find(type);
		if (it != _components.end()) {
			return static_cast<T*>(it->second);
		}
		return nullptr;
	}

	Transform* GetTransform();

	inline EntitySystem* GetEntitySystem() const {
		return _entitySystem;
	}

	void Init();
	void Start();
	void Update(float dt);
	void Draw();

	void SendMessage(std::string const& message, void *data = nullptr);

	friend EntitySystem;
};
