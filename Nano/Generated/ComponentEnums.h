#pragma once

#include <Nano/Engine/Util/Util.h>
#include <typeinfo>

enum ComponentType {
	CT_INVALID,
	CT_Boss,
	CT_EnemyHealth,
	CT_EnemyJumping,
	CT_EnemySpawner,
	CT_EnemyWander,
	CT_Collider,
	CT_Rigidbody,
	CT_Bullet,
	CT_CameraFollow,
	CT_PlayerController,
	CT_RemoveWhenOffscreen,
	CT_Camera,
	CT_HealthBar,
	CT_Renderer,
	CT_SpriteRenderer,
	CT_TextRenderer,
	CT_Tilemap,
	CT_Transform,
	CT_COUNT,
};

class Component;

ComponentType GetComponentType(const std::type_info *type);
ComponentType GetComponentType(String name);
Component* CreateComponentWithName(String name);
Component* CloneComponentWithType(Component const* base, ComponentType type);
