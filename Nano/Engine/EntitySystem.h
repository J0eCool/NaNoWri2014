#pragma once

#include <string>
#include <vector>

class Entity;
class EntityConfig {
};

class EntitySystem {
private:
	std::vector<Entity *> _entities;
	std::vector<Entity *> _entitiesToAdd;
	std::vector<Entity *> _entitiesToRemove;
	EntityConfig *_config;

public:
	EntitySystem(EntityConfig *config);
	~EntitySystem();

	void AddEntity(Entity *entity);
	void RemoveEntity(Entity *entity);
	bool WillRemove(Entity *entity) const;

	EntityConfig* GetConfig() const;
	std::vector<Entity *> const& GetEntities() const;
	Entity* FindEntity(std::string name) const;

	void Update(float dt);
	void Draw();
};
