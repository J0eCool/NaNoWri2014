#include "EntitySystem.h"

#include "Entity.h"

#include <algorithm>

EntitySystem::EntitySystem(EntityConfig *config) : _config(config) {
}

EntitySystem::~EntitySystem() {
	auto entityLists = { _entities, _entitiesToAdd, _entitiesToRemove };
	for (auto list : entityLists) {
		for (auto ent : list) {
			delete ent;
		}
	}
}

void EntitySystem::AddEntity(Entity *entity) {
	_entitiesToAdd.push_back(entity);
}

void EntitySystem::RemoveEntity(Entity *entity) {
	_entitiesToRemove.push_back(entity);
}

bool EntitySystem::WillRemove(Entity *entity) const {
	return std::find(_entitiesToRemove.begin(), _entitiesToRemove.end(), entity) != _entitiesToRemove.end();
}

EntityConfig* EntitySystem::GetConfig() const {
	return _config;
}

Vector<Entity *> const& EntitySystem::GetEntities() const {
	return _entities;
}

Entity* EntitySystem::FindEntity(String name) const {
	for (auto entity : _entities) {
		if (entity->_name == name) {
			return entity;
		}
	}
	return nullptr;
}

struct ShouldRemPred {
	EntitySystem *system;
	ShouldRemPred(EntitySystem *sys) : system(sys) { }
	bool operator()(Entity *ent) {
		return system->WillRemove(ent);
	}
};

void EntitySystem::Update(float dt) {
	// Add queued entities
	for (auto entity : _entitiesToAdd) {
		_entities.push_back(entity);
		entity->_entitySystem = this;
		entity->Init();
	}
	_entitiesToAdd.clear();

	// Update entities
	for (auto entity : _entities) {
		if (!entity->_hasStarted) {
			entity->Start();
			entity->_hasStarted = true;
		}
		entity->Update(dt);
	}

	// Remove queued entities
	for (auto entity : _entitiesToRemove) {
		delete entity;
	}
	auto newEnd = std::remove_if(_entities.begin(), _entities.end(), ShouldRemPred(this));
	if (newEnd != _entities.end()) {
		_entities.erase(newEnd, _entities.end());
	}
	_entitiesToRemove.clear();
}
void EntitySystem::Draw() {
	for (auto entity : _entities) {
		entity->Draw();
	}
}
