#pragma once

#include <string>
#include <typeinfo>

enum ComponentType {
	CT_INVALID,
	CT_Collider,
	CT_Rigidbody,
	CT_Bullet,
	CT_CameraFollow,
	CT_PlayerController,
	CT_Camera,
	CT_Renderer,
	CT_SpriteRenderer,
	CT_TextRenderer,
	CT_SpinningSigma,
	CT_Transform,
};

class Component;

ComponentType GetComponentType(const std::type_info *type);
ComponentType GetComponentType(std::string name);
Component* CreateComponentWithName(std::string name);
