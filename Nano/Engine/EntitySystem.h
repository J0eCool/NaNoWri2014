#pragma once

#include <vector>

class Entity;
class EntityConfig {
};

class EntitySystem {
private:
	std::vector<Entity *> _entities;
	EntityConfig *_config;

public:
	EntitySystem(EntityConfig *config);
	~EntitySystem();

	void AddEntity(Entity *entity);
	void RemoveEntity(Entity *entity);
	std::vector<Entity *> const& GetEntities() const;
	EntityConfig* GetConfig() const;

	void Update(float dt);
	void Draw();
};
