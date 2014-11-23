#pragma once

#include <Nano/Engine/Util/Util.h>
#include <typeinfo>

enum ComponentType {
	CT_INVALID,
	CT_EnemyHealth,
	CT_EnemySpawner,
	CT_Collider,
	CT_Rigidbody,
	CT_Bullet,
	CT_CameraFollow,
	CT_PlayerController,
	CT_RemoveWhenOffscreen,
	CT_Camera,
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
