#include "ComponentEnums.h"

#include <Nano/Engine/Util/Util.h>
#include <Nano/Components/Components.h>

ComponentType GetComponentType(const std::type_info *type) {
	if (type == &typeid(EnemyHealth)) { return CT_EnemyHealth; }
	if (type == &typeid(EnemySpawner)) { return CT_EnemySpawner; }
	if (type == &typeid(Collider)) { return CT_Collider; }
	if (type == &typeid(Rigidbody)) { return CT_Rigidbody; }
	if (type == &typeid(Bullet)) { return CT_Bullet; }
	if (type == &typeid(CameraFollow)) { return CT_CameraFollow; }
	if (type == &typeid(PlayerController)) { return CT_PlayerController; }
	if (type == &typeid(RemoveWhenOffscreen)) { return CT_RemoveWhenOffscreen; }
	if (type == &typeid(Camera)) { return CT_Camera; }
	if (type == &typeid(Renderer)) { return CT_Renderer; }
	if (type == &typeid(SpriteRenderer)) { return CT_SpriteRenderer; }
	if (type == &typeid(TextRenderer)) { return CT_TextRenderer; }
	if (type == &typeid(Transform)) { return CT_Transform; }
	return CT_INVALID;
}

ComponentType GetComponentType(String name) {
	if (name == "EnemyHealth") { return CT_EnemyHealth; }
	if (name == "EnemySpawner") { return CT_EnemySpawner; }
	if (name == "Collider") { return CT_Collider; }
	if (name == "Rigidbody") { return CT_Rigidbody; }
	if (name == "Bullet") { return CT_Bullet; }
	if (name == "CameraFollow") { return CT_CameraFollow; }
	if (name == "PlayerController") { return CT_PlayerController; }
	if (name == "RemoveWhenOffscreen") { return CT_RemoveWhenOffscreen; }
	if (name == "Camera") { return CT_Camera; }
	if (name == "Renderer") { return CT_Renderer; }
	if (name == "SpriteRenderer") { return CT_SpriteRenderer; }
	if (name == "TextRenderer") { return CT_TextRenderer; }
	if (name == "Transform") { return CT_Transform; }
	return CT_INVALID;
}

Component* CreateComponentWithName(String name) {
	if (name == "EnemyHealth") { return new EnemyHealth; }
	if (name == "EnemySpawner") { return new EnemySpawner; }
	if (name == "Collider") { return new Collider; }
	if (name == "Rigidbody") { return new Rigidbody; }
	if (name == "Bullet") { return new Bullet; }
	if (name == "CameraFollow") { return new CameraFollow; }
	if (name == "PlayerController") { return new PlayerController; }
	if (name == "RemoveWhenOffscreen") { return new RemoveWhenOffscreen; }
	if (name == "Camera") { return new Camera; }
	if (name == "Renderer") { return new Renderer; }
	if (name == "SpriteRenderer") { return new SpriteRenderer; }
	if (name == "TextRenderer") { return new TextRenderer; }
	if (name == "Transform") { return new Transform; }
	return nullptr;
}
