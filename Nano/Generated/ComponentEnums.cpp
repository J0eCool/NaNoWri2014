#include "ComponentEnums.h"

#include <string>
#include <map>
#include <Nano/Components/Components.h>

ComponentType GetComponentType(const std::type_info *type) {
	if (type == &typeid(Collider)) { return CT_Collider; }
	if (type == &typeid(Player)) { return CT_Player; }
	if (type == &typeid(Renderer)) { return CT_Renderer; }
	if (type == &typeid(SpriteRenderer)) { return CT_SpriteRenderer; }
	if (type == &typeid(TextRenderer)) { return CT_TextRenderer; }
	if (type == &typeid(SpinningSigma)) { return CT_SpinningSigma; }
	if (type == &typeid(Transform)) { return CT_Transform; }
	return CT_INVALID;
}

ComponentType GetComponentType(std::string name) {
	if (name == "Collider") { return CT_Collider; }
	if (name == "Player") { return CT_Player; }
	if (name == "Renderer") { return CT_Renderer; }
	if (name == "SpriteRenderer") { return CT_SpriteRenderer; }
	if (name == "TextRenderer") { return CT_TextRenderer; }
	if (name == "SpinningSigma") { return CT_SpinningSigma; }
	if (name == "Transform") { return CT_Transform; }
	return CT_INVALID;
}

Component* CreateComponentWithName(std::string name) {
	if (name == "Collider") { return new Collider; }
	if (name == "Player") { return new Player; }
	if (name == "Renderer") { return new Renderer; }
	if (name == "SpriteRenderer") { return new SpriteRenderer; }
	if (name == "TextRenderer") { return new TextRenderer; }
	if (name == "SpinningSigma") { return new SpinningSigma; }
	if (name == "Transform") { return new Transform; }
	return nullptr;
}
