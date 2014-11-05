#pragma once

#include <vector>

class Entity;

class EntitySystem {
private:
	std::vector<Entity *> _entities;

public:
	~EntitySystem();

	void AddEntity(Entity *entity);
	void RemoveEntity(Entity *entity);
	std::vector<Entity *> const& GetEntities() const;

	void Update(float dt);
	void Draw();
};
