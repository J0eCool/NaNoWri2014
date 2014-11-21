#include "EntitySystem.h"

#include "Entity.h"

#include <algorithm>

EntitySystem::EntitySystem(EntityConfig *config) : _config(config) {
}

template <typename T>
void deleteAll(T const& collection) {
	for (auto item : collection) {
		delete item;
	}
}

EntitySystem::~EntitySystem() {
	deleteAll(_entities);
	deleteAll(_entitiesToAdd);
	deleteAll(_entitiesToRemove);
}

void EntitySystem::AddEntity(Entity *entity) {
	_entitiesToAdd.push_back(entity);
	entity->_entitySystem = this;
	entity->Init();
}

void EntitySystem::RemoveEntity(Entity *entity) {
	_entitiesToRemove.insert(entity);
}

bool EntitySystem::WillRemove(Entity *entity) const {
	return _entitiesToRemove.find(entity) != _entitiesToRemove.end();
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
	}
	_entitiesToAdd.clear();

	// Update entities
	for (auto entity : _entities) {
		if (!entity->_hasStarted) {
			entity->Start();
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
