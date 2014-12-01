#include "Boss.h"

#include <Nano/Components/Components.h>

Boss::Boss() : _state(BS_Start), _dir(1), _timer(0.0f), _counter(0) {
}

void Boss::Start() {
	auto health = GetComponent<EnemyHealth>();
	auto curHealth = [health](){ return health->GetHealth(); };
	auto maxHealth = [health](){ return health->GetMaxHealth(); };
	GetEntitySystem()->FindEntity("BossHealthBar")->GetComponent<HealthBar>()->SetFunctions(curHealth, maxHealth);
	_player = GetEntitySystem()->FindEntity("Player");

	_bulletPrefab = LoadPrefabFromFile("../Assets/Prefabs/EnemyBullet.prefab");
}

void Boss::Deinit() {
	GetEntitySystem()->FindEntity("BossHealthBar")->GetComponent<HealthBar>()->SetFunctions(nullptr, nullptr);
	delete _bulletPrefab;
}

void Boss::Update(float dt) {
	auto renderer = GetComponent<SpriteRenderer>();
	auto rigidbody = GetComponent<Rigidbody>();

	const float kMoveWidth = 550.0f;
	const float kStartDelay = 0.75f;
	const float kHopTime = 0.7f;
	const float kHopDelay = 0.15f;
	const int kNumHops = 3;
	const float kDashTime = 0.65f;
	const float kDashDelay = 0.75f;
	const float kJumpTime = 1.05f;
	const float kJumpDelay = 0.5f;

	BossState newState = BS_NONE;

	Vec2 shotDir(0.0f, 0.0f);
	Vec2 center = GetTransform()->GetCenter();
	bool shouldShoot = !_shotTimes.empty() && _timer > _shotTimes.front();
	if (shouldShoot) {
		_shotTimes.pop();
	}

	switch (_state) {
	case BS_Start:
		if (_timer > kStartDelay) {
			newState = getNextState();
		}
		break;
	case BS_Hop:
		if (rigidbody->IsColliding(CD_Down)) {
			if (_counter >= kNumHops) {
				newState = getNextState();
			}
			else if (_timer > kHopDelay) {
				float spd = kMoveWidth / (kHopTime * kNumHops);
				rigidbody->vel = { _dir * spd, -Rigidbody::kGravity * kHopTime / 2.0f };
				_counter++;
				_timer = -kHopTime;
				if (_counter < kNumHops) {
					_shotTimes.push(-kHopTime * 3.0f / 4.0f);
				}
			}
			else {
				rigidbody->vel.x = 0.0f;
			}
		}
		if (shouldShoot) {
			shotDir = _player->GetTransform()->GetCenter() - center - Vec2(0.0f, 8.0f);
		}
		break;
	case BS_Dash:
		if (_counter == 0) {
			if (_timer > kDashDelay) {
				_counter++;
				_timer = 0.0f;
				_shotTimes.push(kDashTime * 0.0f);
				_shotTimes.push(kDashTime * 0.35f);
			}
			else {
				rigidbody->vel.x = 0.0f;
			}
		}
		else if (_counter == 1) {
			float spd = _dir * kMoveWidth / kDashTime;
			rigidbody->vel.x = spd;
			if (_timer > kDashTime) {
				newState = getNextState();
			}
		}
		if (shouldShoot) {
			shotDir = { (float)_dir, -1.0f };
		}
		break;
	case BS_Jump:
		if (rigidbody->IsColliding(CD_Down)) {
			if (_counter >= 1) {
				newState = getNextState();
			}
			else if (_timer > kJumpDelay) {
				float spd = kMoveWidth / kJumpTime;
				rigidbody->vel = { _dir * spd, -Rigidbody::kGravity * kJumpTime / 2.0f };
				_counter++;
				_timer = 0.0f;
				_shotTimes.push(kJumpTime * 0.25f);
				_shotTimes.push(kJumpTime * 0.5f);
				_shotTimes.push(kJumpTime * 0.75f);
			}
			else {
				rigidbody->vel.x = 0.0f;
			}
		}
		if (shouldShoot) {
			shotDir = { 0.0f, 1.0f };
		}
		break;
	}

	_timer += dt;
	if (shotDir.LengthSquared() > 0.0f) {
		Entity *bullet = new Entity(*_bulletPrefab);
		Vec2 center = GetTransform()->GetCenter();
		bullet->GetTransform()->pos = center;
		bullet->GetComponent<Bullet>()->SetDir(shotDir);
		GetEntitySystem()->AddEntity(bullet);
	}

	if (newState != BS_NONE) {
		_state = newState;
		_dir = -_dir;
		_timer = 0.0f;
		_counter = 0;
		_shotTimes = Queue<float>();
	}

	renderer->GetSprite()->horizFlip = _dir < 0;
}

BossState Boss::getNextState() {
	Vector<BossState> states{ BS_Hop, BS_Jump, BS_Dash };
	for (int i = states.size() - 1; i >= 0; --i) {
		if (states[i] != _state) {
			states.push_back(states[i]);
		}
	}
	return states[randInt(0, states.size())];
}
