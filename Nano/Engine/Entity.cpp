#include "Entity.h"

#include "Component.h"
#include "Transform.h"

Entity::Entity(String name) : _name(name) {
}

Entity::~Entity() {
	for (auto kv : _components) {
		delete kv.second;
	}
}

Component* Entity::AddComponent(Component* component) {
	auto type = component->_type;
	if (!_components[type]) {
		component->_entity = this;
		_components[type] = component;
	}
	else {
		LogError("Entity (", _name, "): Adding component with type=", (int)type, " that already exists!");
	}
	if (_entitySystem) {
		LogError("Entity (", _name, "): Adding component with type=", (int)type, " on entity that was already added to an entity system! TODO: make that not an error");
	}
	return _components[type];
}

Transform* Entity::GetTransform() {
	return GetComponent<Transform>();
}

void Entity::SendMessage(String const& message, void *data) {
	for (auto kv : _components) {
		kv.second->HandleMessage(message, data);
	}
}
