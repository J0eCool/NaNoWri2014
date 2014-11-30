#include "EnemyHealth.h"

#include "EnemySpawner.h"

void EnemyHealth::Start() {
	_health = _maxHealth;
}

void EnemyHealth::Deinit() {
	if (_spawner) {
		_spawner->HandleDespawn(_entity);
	}
}

void EnemyHealth::HandleMessage(String const& message, void *data) {
	if (message == "BulletHit") {
		int damage = *(int *)data;
		_health -= damage;
		if (_health <= 0) {
			GetEntitySystem()->RemoveEntity(_entity);
		}
	}
}

void EnemyHealth::SetSpawner(EnemySpawner *spawner) {
	_spawner = spawner;
}

int EnemyHealth::GetHealth() const {
	return _health;
}

int EnemyHealth::GetMaxHealth() const {
	return _maxHealth;
}
