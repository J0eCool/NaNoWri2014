#include "Entity.h"

#include "EntitySystem.h"
#include "Component.h"
#include "Transform.h"

Entity::Entity(String name) : _name(name), _components(CT_COUNT) {
}

Entity::Entity(Entity const& other) : Entity(other._name) {
	for (auto oCmp : other._components) {
		if (oCmp) {
			auto cmp = oCmp->Clone();
			_components[cmp->_type] = cmp;
			cmp->_entity = this;
		}
	}
	//for (unsigned i = 0; i < other._components.size(); ++i) {
	//	_components[i] = other._components[i]->Clone();
	//}
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
