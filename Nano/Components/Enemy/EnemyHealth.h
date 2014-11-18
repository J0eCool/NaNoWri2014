#pragma once

#include <Nano/Engine/Engine.h>

class EnemySpawner;

class EnemyHealth : public Component {
private:
	int _maxHealth;
	int _health;

	EnemySpawner *_spawner;

public:
	//$$_maxHealth:Int
	void LoadArg(String const& key, String const& val) override;

	void Start() override;
	void HandleMessage(String const& message, void *data) override;

	void SetSpawner(EnemySpawner *spawner);
};
