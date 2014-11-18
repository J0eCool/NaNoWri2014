#include "EnemyHealth.h"

void EnemyHealth::Start() {
	_health = _maxHealth;
}

void EnemyHealth::HandleMessage(std::string const& message, void *data) {
	if (message == "BulletHit") {
		_health -= 1;
		if (_health <= 0) {
			GetEntitySystem()->RemoveEntity(_entity);
		}
	}
}
