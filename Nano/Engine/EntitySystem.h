#pragma once

#include "Util/Util.h"

#include <vector>

class Entity;
class Component;

class EntityConfig {
};

class EntitySystem {
private:
	Set<Entity *> _entities;
	Set<Entity *> _entitiesToAdd;
	Set<Entity *> _entitiesToRemove;
	Dict<float, Set<Component *>> _components;
	EntityConfig *_config;

public:
	EntitySystem(EntityConfig *config);
	~EntitySystem();

	void AddEntity(Entity *entity);
	void RemoveEntity(Entity *entity);
	bool WillRemove(Entity *entity) const;

	EntityConfig* GetConfig() const;
	Set<Entity *> const& GetEntities() const;
	Entity* FindEntity(String name) const;

	void Update(float dt);
	void Draw();
};
