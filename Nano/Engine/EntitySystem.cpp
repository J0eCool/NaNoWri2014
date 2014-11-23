#include "EntitySystem.h"

#include "Component.h"
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
	_entitiesToAdd.insert(entity);
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

Set<Entity *> const& EntitySystem::GetEntities() const {
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
		_entities.insert(entity);
		for (auto kv : entity->_components) {
			_components[kv.second->priority()].insert(kv.second);
		}
	}
	_entitiesToAdd.clear();

	// Update entities
	for (auto kv : _components) {
		for (auto component : kv.second) {
			if (!component->_hasStarted) {
				component->Start();
				component->_hasStarted = true;
			}
			component->Update(dt);
		}
	}

	// Remove queued entities
	for (auto entity : _entitiesToRemove) {
		for (auto kv : entity->_components) {
			_components[kv.second->priority()].erase(kv.second);
		}
		_entities.erase(entity);
		delete entity;
	}
	_entitiesToRemove.clear();
}
void EntitySystem::Draw() {
	for (auto kv : _components) {
		for (auto component : kv.second) {
			component->Draw();
		}
	}
}
