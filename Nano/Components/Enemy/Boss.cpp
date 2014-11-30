#include "Boss.h"

#include <Nano/Components/Components.h>

void Boss::Start() {
	auto health = GetComponent<EnemyHealth>();
	auto curHealth = [health](){ return health->GetHealth(); };
	auto maxHealth = [health](){ return health->GetMaxHealth(); };
	GetEntitySystem()->FindEntity("BossHealthBar")->GetComponent<HealthBar>()->SetFunctions(curHealth, maxHealth);
}

void Boss::Deinit() {
	GetEntitySystem()->FindEntity("BossHealthBar")->GetComponent<HealthBar>()->SetFunctions(nullptr, nullptr);
}
