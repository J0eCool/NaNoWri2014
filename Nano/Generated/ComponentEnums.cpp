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
	if (type == &typeid(Tilemap)) { return CT_Tilemap; }
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
	if (name == "Tilemap") { return CT_Tilemap; }
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
	if (name == "Tilemap") { return new Tilemap; }
	if (name == "Transform") { return new Transform; }
	return nullptr;
}

Component* CloneComponentWithType(Component const* base, ComponentType type) {
	Component *cmp = nullptr;
	if (type == CT_EnemyHealth) { cmp = new EnemyHealth; memcpy(cmp, base, sizeof(EnemyHealth)); }
	if (type == CT_EnemySpawner) { cmp = new EnemySpawner; memcpy(cmp, base, sizeof(EnemySpawner)); }
	if (type == CT_Collider) { cmp = new Collider; memcpy(cmp, base, sizeof(Collider)); }
	if (type == CT_Rigidbody) { cmp = new Rigidbody; memcpy(cmp, base, sizeof(Rigidbody)); }
	if (type == CT_Bullet) { cmp = new Bullet; memcpy(cmp, base, sizeof(Bullet)); }
	if (type == CT_CameraFollow) { cmp = new CameraFollow; memcpy(cmp, base, sizeof(CameraFollow)); }
	if (type == CT_PlayerController) { cmp = new PlayerController; memcpy(cmp, base, sizeof(PlayerController)); }
	if (type == CT_RemoveWhenOffscreen) { cmp = new RemoveWhenOffscreen; memcpy(cmp, base, sizeof(RemoveWhenOffscreen)); }
	if (type == CT_Camera) { cmp = new Camera; memcpy(cmp, base, sizeof(Camera)); }
	if (type == CT_Renderer) { cmp = new Renderer; memcpy(cmp, base, sizeof(Renderer)); }
	if (type == CT_SpriteRenderer) { cmp = new SpriteRenderer; memcpy(cmp, base, sizeof(SpriteRenderer)); }
	if (type == CT_TextRenderer) { cmp = new TextRenderer; memcpy(cmp, base, sizeof(TextRenderer)); }
	if (type == CT_Tilemap) { cmp = new Tilemap; memcpy(cmp, base, sizeof(Tilemap)); }
	if (type == CT_Transform) { cmp = new Transform; memcpy(cmp, base, sizeof(Transform)); }
	return cmp;
}
