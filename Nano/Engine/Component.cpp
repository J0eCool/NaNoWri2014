#include "Component.h"

#include "Entity.h"
#include "EntitySystem.h"
#include "Transform.h"

Transform* Component::GetTransform() {
	return GetComponent<Transform>();
}

EntitySystem* Component::GetEntitySystem() {
	return _entity->GetEntitySystem();
}