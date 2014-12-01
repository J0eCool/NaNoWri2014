#include "PlayerController.h"

#include <Nano/Managers/InputManager.h>
#include <Nano/Constants.h>

#include <Nano/Components/Components.h>

PlayerController::PlayerController() : _speed(350.0f), _jumpHeight(180.0f), _normalShots(3),
		_specialShots(1), _health(_maxHealth), _mana(_maxMana) {
}

void PlayerController::Start() {
	_startPos = GetTransform()->pos;
	auto curHealth = [this](){ return _health; };
	auto maxHealth = [this](){ return _maxHealth; };
	GetEntitySystem()->FindEntity("PlayerHealthBar")->GetComponent<HealthBar>()->SetFunctions(curHealth, maxHealth);
	//auto curMana = [this](){ return _mana; };
	//auto maxMana = [this](){ return _maxMana; };
	//GetEntitySystem()->FindEntity("PlayerManaBar")->GetComponent<HealthBar>()->SetFunctions(curMana, maxMana);
}

void PlayerController::Update(float dt) {
	InputManager *input = InputManager::GetInstance();
	Transform *transform = _entity->GetTransform();
	Rigidbody *rigidbody = GetComponent<Rigidbody>();
	Vec2 vel = rigidbody->vel;
	if (canControl()) {
		vel.x = _speed * input->GetAxis(IA_Horizontal);
		if (sign(vel.x)) {
			_facingDir = sign(vel.x);
		}
		float gDir = 1.0f;
		if (rigidbody->IsColliding(CD_Down)) {
			if (input->IsDown(IT_Jump)) {
				vel.y = -gDir * sqrt(2.0f * _jumpHeight * Rigidbody::kGravity);
				_isHoldingJump = true;
			}
		}
		if (_isHoldingJump && !input->IsHeld(IT_Jump)) {
			_isHoldingJump = false;
			if (vel.y * gDir < 0.0f) {
				vel.y *= 0.35f;
			}
		}
		rigidbody->vel = vel;

		String bulletFile;
		Bullet::Container *container = nullptr;
		if (input->IsDown(IT_Special)) {
			bulletFile = "../Assets/Prefabs/BigBullet.prefab";
			container = &_specialShots;
		}
		else if (input->IsDown(IT_Shoot)) {
			bulletFile = "../Assets/Prefabs/Bullet.prefab";
			container = &_normalShots;
		}
		if (container && !container->IsFull()) {
			Entity *bullet = LoadPrefabFromFile(bulletFile);
			Vec2 bulletSize = bullet->GetTransform()->size;
			auto offset = _shotOffset;
			offset.x *= _facingDir;
			offset -= bulletSize / 2.0f;
			bullet->GetTransform()->pos = transform->pos + transform->size / 2.0f + offset;
			bullet->GetTransform()->size = bulletSize;
			bullet->GetComponent<Bullet>()->SetDir({ (float)_facingDir, 0 });

			GetEntitySystem()->AddEntity(bullet);

			bullet->GetComponent<SpriteRenderer>()->GetSprite()->horizFlip = _facingDir < 0;
			container->AddBullet(bullet->GetComponent<Bullet>());
		}
	}

	_invinTimer -= dt;

	if (!IsInvincible()) {
		auto collider = GetComponent<Collider>();
		auto collided = collider->GetCollidedEntities();
		for (auto ent : collided) {
			if (ent->GetComponent<Boss>()) {
				takeDamage(4);
			}
			else if (ent->GetComponent<EnemyHealth>()) {
				takeDamage(2);
			}
		}
	}

	auto sprite = GetComponent<SpriteRenderer>()->GetSprite();
	sprite->horizFlip = _facingDir < 0;
	sprite->color.a = lerp(_invinTimer / _invinMaxTime, 0xff, 0x60);
}

void PlayerController::HandleMessage(String const& message, void* data) {
	if (message == "BulletHit" && _invinTimer <= 0.0f) {
		takeDamage(*(int *)data);
	}
}

bool PlayerController::canControl() {
	return _invinTimer < _invinMaxTime - _noControlTime;
}

bool PlayerController::IsInvincible() {
	return _invinTimer > 0.0f;
}

void PlayerController::takeDamage(int damage) {
	_health -= damage;
	if (_health <= 0) {
		GetTransform()->pos = _startPos;
		_health = _maxHealth;
		_mana = _maxMana;
	}
	else {
		_invinTimer = _invinMaxTime;
		GetComponent<Rigidbody>()->vel = Vec2(-(float)_facingDir, -1.25f) * 350.0f;
	}
}
