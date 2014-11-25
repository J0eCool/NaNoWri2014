#include "EnemySpawner.h"

#include <Nano/Components/Components.h>

EnemySpawner::EnemySpawner() : _wasOffscreen(true) {
}

void EnemySpawner::spawnEnemy() {
	Transform *transform = GetTransform();
	Vec2 spawnPoint = transform->pos;

	Entity *enemy = LoadPrefabFromFile("../Assets/Prefabs/" + _spawnName + ".prefab");
	enemy->GetTransform()->pos = spawnPoint;
	enemy->GetComponent<EnemyHealth>()->SetSpawner(this);
	GetEntitySystem()->AddEntity(enemy);
	_spawnedEntity = enemy;
}

void EnemySpawner::Update(float dt) {
	auto remover = GetComponent<RemoveWhenOffscreen>();
	bool offscreen = remover->IsOffscreen();
	if (_wasOffscreen && !offscreen && !_spawnedEntity) {
		spawnEnemy();
	}
	_wasOffscreen = offscreen;
}

void EnemySpawner::HandleDespawn(Entity *entity) {
	if (entity = _spawnedEntity) {
		_spawnedEntity = nullptr;
	}
}
