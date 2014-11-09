#include "EntitySystem.h"

#include "Entity.h"

EntitySystem::EntitySystem(EntityConfig *config) : _config(config) {
}

EntitySystem::~EntitySystem() {
	for (auto it = _entities.begin(); it != _entities.end(); ++it) {
		delete *it;
	}
}

void EntitySystem::AddEntity(Entity *entity) {
	_entities.push_back(entity);
	entity->_entitySystem = this;
	entity->Start();
}

void EntitySystem::RemoveEntity(Entity *entity) {
	for (auto it = _entities.begin(); it != _entities.end(); ++it) {
		if (*it == entity) {
			delete *it;
			_entities.erase(it);
			return;
		}
	}
}

std::vector<Entity *> const& EntitySystem::GetEntities() const {
	return _entities;
}

EntityConfig* EntitySystem::GetConfig() const {
	return _config;
}

void EntitySystem::Update(float dt) {
	for (auto entity : _entities) {
		entity->Update(dt);
	}
}
void EntitySystem::Draw() {
	for (auto entity : _entities) {
		entity->Draw();
	}
}
