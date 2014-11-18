#pragma once

#include <Nano/Engine/Engine.h>

class EnemySpawner : public Component {
private:
	int _spawnLimit;
	Vector<Entity*> _spawnedEntities;

	void SpawnEnemy();

public:
	//$$_spawnLimit:Int
	void LoadArg(String const& key, String const& val) override;
	void Update(float dt) override;

	void HandleDespawn(Entity *entity);
};
