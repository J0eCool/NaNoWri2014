#include "ComponentEnums.h"

#include <string>
#include <map>
#include <Nano/Components/Components.h>

ComponentType GetComponentType(const std::type_info *type) {
	if (type == &typeid(Collider)) { return CT_Collider; }
	if (type == &typeid(Rigidbody)) { return CT_Rigidbody; }
	if (type == &typeid(PlayerController)) { return CT_PlayerController; }
	if (type == &typeid(Camera)) { return CT_Camera; }
	if (type == &typeid(Renderer)) { return CT_Renderer; }
	if (type == &typeid(SpriteRenderer)) { return CT_SpriteRenderer; }
	if (type == &typeid(TextRenderer)) { return CT_TextRenderer; }
	if (type == &typeid(SpinningSigma)) { return CT_SpinningSigma; }
	if (type == &typeid(Transform)) { return CT_Transform; }
	return CT_INVALID;
}

ComponentType GetComponentType(std::string name) {
	if (name == "Collider") { return CT_Collider; }
	if (name == "Rigidbody") { return CT_Rigidbody; }
	if (name == "PlayerController") { return CT_PlayerController; }
	if (name == "Camera") { return CT_Camera; }
	if (name == "Renderer") { return CT_Renderer; }
	if (name == "SpriteRenderer") { return CT_SpriteRenderer; }
	if (name == "TextRenderer") { return CT_TextRenderer; }
	if (name == "SpinningSigma") { return CT_SpinningSigma; }
	if (name == "Transform") { return CT_Transform; }
	return CT_INVALID;
}

Component* CreateComponentWithName(std::string name) {
	if (name == "Collider") { return new Collider; }
	if (name == "Rigidbody") { return new Rigidbody; }
	if (name == "PlayerController") { return new PlayerController; }
	if (name == "Camera") { return new Camera; }
	if (name == "Renderer") { return new Renderer; }
	if (name == "SpriteRenderer") { return new SpriteRenderer; }
	if (name == "TextRenderer") { return new TextRenderer; }
	if (name == "SpinningSigma") { return new SpinningSigma; }
	if (name == "Transform") { return new Transform; }
	return nullptr;
}
