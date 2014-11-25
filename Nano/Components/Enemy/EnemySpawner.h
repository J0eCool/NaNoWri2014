#pragma once

#include <Nano/Engine/Engine.h>

class EnemySpawner : public Component {
private:
	String _spawnName;

	Entity *_spawnedEntity;
	bool _wasOffscreen;

	void spawnEnemy();

public:
	EnemySpawner();

	//$$_spawnName:String
	void LoadArg(String const& key, String const& val) override;
	void Update(float dt) override;

	void HandleDespawn(Entity *entity);
};
