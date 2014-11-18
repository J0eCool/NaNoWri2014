#include "EnemySpawner.h"

#include <Nano/Components/Components.h>

void EnemySpawner::SpawnEnemy() {
	Transform *transform = GetTransform();
	Vec2 spawnPoint = Vec2::Rand(transform->pos, transform->pos + transform->size);

	Entity *enemy = new Entity("Enemy");
	enemy->AddComponent(CT_Collider, (new Collider())->SetArg("layerMask", "0x2"));
	enemy->AddComponent(CT_Rigidbody, new Rigidbody());
	enemy->AddComponent(CT_EnemyHealth, (new EnemyHealth())->SetArg("maxHealth", "2"));
	enemy->AddComponent(CT_SpriteRenderer, (new SpriteRenderer())->SetArg("spriteName", "Slime"));
	enemy->AddComponent(CT_Transform, new Transform());
	enemy->GetTransform()->pos = spawnPoint;
	enemy->GetTransform()->size = Vec2(65, 120);
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
