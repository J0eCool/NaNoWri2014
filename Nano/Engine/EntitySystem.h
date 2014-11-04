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

	void Update(float dt);
	void Draw();
};
