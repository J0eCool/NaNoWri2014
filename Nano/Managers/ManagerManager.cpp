#include "ManagerManager.h"

#include "AssetManager.h"
#include "InputManager.h"

void ManagerManager::Init() {
	AssetManager::GetInstance()->Init();
	InputManager::GetInstance()->Init();
}

void ManagerManager::Deinit() {
	InputManager::GetInstance()->Deinit();
	AssetManager::GetInstance()->Deinit();
}

void ManagerManager::Update(float dt) {
	InputManager::GetInstance()->Update();
}
