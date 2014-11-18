#pragma once

#include "Util/Util.h"

#include <vector>

class Entity;
class EntityConfig {
};

class EntitySystem {
private:
	Vector<Entity *> _entities;
	Vector<Entity *> _entitiesToAdd;
	Set<Entity *> _entitiesToRemove;
	EntityConfig *_config;

public:
	EntitySystem(EntityConfig *config);
	~EntitySystem();

	void AddEntity(Entity *entity);
	void RemoveEntity(Entity *entity);
	bool WillRemove(Entity *entity) const;

	EntityConfig* GetConfig() const;
	Vector<Entity *> const& GetEntities() const;
	Entity* FindEntity(String name) const;

	void Update(float dt);
	void Draw();
};
