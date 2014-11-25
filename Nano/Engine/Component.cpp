#include "Component.h"

#include "Entity.h"
#include "EntitySystem.h"
#include "Transform.h"

Component* Component::Clone() const {
	return CloneComponentWithType(this, _type);
}

Transform* Component::GetTransform() {
	return GetComponent<Transform>();
}

EntitySystem* Component::GetEntitySystem() {
	return _entity->GetEntitySystem();
}