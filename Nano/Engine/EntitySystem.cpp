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

EntityConfig* EntitySystem::GetConfig() const {
	return _config;
}

std::vector<Entity *> const& EntitySystem::GetEntities() const {
	return _entities;
}

Entity* EntitySystem::FindEntity(std::string name) const {
	for (auto entity : _entities) {
		if (entity->_name == name) {
			return entity;
		}
	}
	return nullptr;
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
