#include "EntitySystem.h"

#include "Component.h"
#include "Entity.h"

#include <algorithm>

template <typename T>
void deleteAll(T const& collection) {
	for (auto item : collection) {
		delete item;
	}
}

template <typename T, typename F>
inline void forAllComponents(T const& components, F func) {
	for (auto kv : components) {
		for (auto c : kv.second) {
			func(c);
		}
	}
}

EntitySystem::EntitySystem(EntityConfig *config) : _config(config) {
}

EntitySystem::~EntitySystem() {
	forAllComponents(_components, [](Component *component){
		component->Deinit();
	});

	deleteAll(_entities);
	deleteAll(_entitiesToAdd);
	deleteAll(_entitiesToRemove);
}

void EntitySystem::AddEntity(Entity *entity) {
	_entitiesToAdd.insert(entity);
	entity->_entitySystem = this;
	entity->forAllComponents([](Component* cmp) {
		cmp->Init();
	});
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
		entity->forAllComponents([this](Component* cmp) {
			_components[cmp->priority()].insert(cmp);
		});
	}
	_entitiesToAdd.clear();

	// Update entities
	forAllComponents(_components, [dt](Component *component) {
		if (!component->_hasStarted) {
			component->Start();
			component->_hasStarted = true;
		}
		component->Update(dt);
	});

	// Remove queued entities
	for (auto entity : _entitiesToRemove) {
		entity->forAllComponents([this](Component* cmp) {
			_components[cmp->priority()].erase(cmp);
			cmp->Deinit();
		});
		_entities.erase(entity);
		delete entity;
	}
	_entitiesToRemove.clear();
}

void EntitySystem::Draw() {
	forAllComponents(_components, [](Component *component) {
		component->Draw();
	});
}
