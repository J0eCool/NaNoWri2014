#include "Entity.h"

#include "EntitySystem.h"
#include "Component.h"
#include "Transform.h"

Entity::Entity(String name) : _name(name) {
}

Entity::Entity(Entity& other) : Entity(other._name) {
	other.forAllComponents([this](Component* oCmp) {
		auto cmp = oCmp->Clone();
			cmp->_type = oCmp->_type;
			_components[cmp->_type] = cmp;
			cmp->_entity = this;
	});
	if (other._entitySystem) {
		other._entitySystem->AddEntity(this);
	}
}

Entity::~Entity() {
	forAllComponents([](Component* cmp) {
		delete cmp;
	});
}

Component* Entity::AddComponent(Component* component) {
	auto type = component->_type;
	if (!_components[type]) {
		component->_entity = this;
		_components[type] = component;
	}
	else {
		LogError("Entity (", _name, "): Adding component with type=", (int)type, " that already exists!");
	}
	if (_entitySystem) {
		LogError("Entity (", _name, "): Adding component with type=", (int)type, " on entity that was already added to an entity system! TODO: make that not an error");
	}
	return _components[type];
}

Transform* Entity::GetTransform() {
	return GetComponent<Transform>();
}

void Entity::SendMessage(String const& message, void *data) {
	forAllComponents([&message, &data](Component* cmp) {
		cmp->HandleMessage(message, data);
	});
}
