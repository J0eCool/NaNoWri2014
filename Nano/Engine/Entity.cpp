#include "Entity.h"

#include "Component.h"
#include "Transform.h"

Entity::Entity() {
}

Entity::Entity(std::initializer_list<Component *> components) {
	for (auto it = components.begin(); it != components.end(); ++it) {
		auto t = &typeid(**it);
		_components[t] = *it;
		(*it)->_entity = this;
	}
}

Entity::~Entity() {
	for (auto it = _components.begin(); it != _components.end(); ++it) {
		delete it->second;
	}
}

Transform* Entity::GetTransform() const {
	return GetComponent<Transform>();
}

void Entity::Start() {
	for (auto kv : _components) {
		kv.second->Start();
	}
}

void Entity::Update(float dt) {
	for (auto it = _components.begin(); it != _components.end(); ++it) {
		it->second->Update(dt);
	}
}

void Entity::Draw() {
	for (auto it = _components.begin(); it != _components.end(); ++it) {
		it->second->Draw();
	}
}
