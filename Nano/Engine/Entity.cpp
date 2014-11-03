#include "Entity.h"

#include "Component.h"

Entity::~Entity() {
	for (auto it = _components.begin(); it != _components.end(); ++it) {
		delete it->second;
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
