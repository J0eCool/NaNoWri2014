#include "EnemySpawner.h"

#include <Nano/Components/Components.h>

void EnemySpawner::SpawnEnemy() {
	Transform *transform = GetTransform();
	Vec2 spawnPoint = Vec2::Rand(transform->pos, transform->pos + transform->size);

	Entity *enemy = LoadPrefabFromFile("../Assets/Prefabs/Slime.prefab");
	enemy->GetTransform()->pos = spawnPoint;
	enemy->GetComponent<EnemyHealth>()->SetSpawner(this);
	GetEntitySystem()->AddEntity(enemy);
	_spawnedEntities.push_back(enemy);
}

void EnemySpawner::Update(float dt) {
	if ((int)_spawnedEntities.size() < _spawnLimit) {
		SpawnEnemy();
	}
}

void EnemySpawner::HandleDespawn(Entity *entity) {
	for (auto it = _spawnedEntities.begin(); it != _spawnedEntities.end(); ++it) {
		if (*it == entity) {
			_spawnedEntities.erase(it);
			break;
		}
	}
}
