#include "ComponentFactory.h"

#include "Util/Util.h"

#include "Component.h"
#include "Entity.h"
#include "EntitySystem.h"

#include <fstream>
#include <sstream>

Component* CreateComponentFromStringArray(std::vector<std::string> parts) {
	Component* cmp = CreateComponentWithName(parts[0]);
	//if (!cmp) {
	//	Log("Component of type ", parts[0], " does not exist!");
	//	return nullptr;
	//}
	//parts.erase(parts.begin());
	//cmp->Load(parts);
	return cmp;
}

Component* CreateComponentFromString(std::string string) {
	auto parts = SplitString(string);
	return CreateComponentFromStringArray(parts);
}

void AddStringComponentToEntity(Entity *entity, std::string str) {
	auto parts = SplitString(str);
	Component *cmp = CreateComponentFromStringArray(parts);
	entity->AddComponent(GetComponentType(parts[0]), cmp);
}

Entity* CreateEntityFromString(std::string string) {
	auto parts = SplitString(string, '\n');
	Entity *entity = new Entity(parts[0]);
	parts.erase(parts.begin());
	for (auto str : parts) {
		AddStringComponentToEntity(entity, str);
	}
	return entity;
}

void AddEntitiesFromFile(EntitySystem& system, std::string filename) {
	std::ifstream file(filename.c_str());
	std::string line;
	Entity *entity = nullptr;
	Component *component = nullptr;
	ComponentType componentType = CT_INVALID;
	if (std::getline(file, line)) {
		entity = new Entity(line);
	}
	bool readNext = true;
	int tabs = 0;
	while (!(readNext && !std::getline(file, line))) {
		if (readNext) {
			tabs = TabCount(line);
			line = Trim(line);
		}
		readNext = true;

		if (!entity) {
			if (line != "") {
				entity = new Entity(line);
			}
		}
		else if (!component) {
			if (tabs == 1) {
				component = CreateComponentWithName(line);
				componentType = GetComponentType(line);
			}
			else {
				system.AddEntity(entity);
				entity = nullptr;
				readNext = false;
			}
		}
		else {
			if (tabs == 2) {
				auto kv = SplitString(line, ':');
				component->LoadArg(Trim(kv[0]), Trim(kv[1]));
			}
			else {
				entity->AddComponent(componentType, component);
				component = nullptr;
				readNext = false;
			}
		}
	}
	if (component) {
		entity->AddComponent(componentType, component);
	}
	if (entity) {
		system.AddEntity(entity);
	}
}
