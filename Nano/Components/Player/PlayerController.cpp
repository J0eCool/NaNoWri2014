#include "PlayerController.h"

#include <Nano/Managers/InputManager.h>
#include <Nano/Constants.h>

#include <Nano/Components/Components.h>

PlayerController::PlayerController() : _speed(350.0f), _jumpHeight(180.0f), _normalShots(3), _specialShots(1) {
}

void PlayerController::Update(float dt) {
	InputManager *input = InputManager::GetInstance();
	Transform *transform = _entity->GetTransform();
	Rigidbody *rigidbody = GetComponent<Rigidbody>();
	Vec2 vel = rigidbody->vel;
	vel.x = _speed * input->GetAxis(IA_Horizontal);
	if (sign(vel.x)) {
		_facingDir = sign(vel.x);
	}

	auto collided = GetComponent<Rigidbody>()->GetCollisionDirs();
	float gDir = 1.0f;
	if (collided & CD_Down) {
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

	GetComponent<SpriteRenderer>()->GetSprite()->horizFlip = _facingDir < 0;

	Entity* text = _entity->GetEntitySystem()->FindEntity("PlayerPosText");
	if (text) {
		text->GetComponent<TextRenderer>()->SetText(transform->pos.ToString());
	}
}
