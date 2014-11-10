#pragma once

#include <Nano/Generated/ComponentEnums.h>
#include <Nano/Engine/Engine.h>
#include "Util/StringHandling.h"

#include "Util/Util.h"

#include <string>
#include <fstream>

Component* CreateComponentFromStringArray(std::vector<std::string> parts) {
	Component* cmp = CreateComponentWithName(parts[0]);
	if (!cmp) {
		Log("Component of type ", parts[0], " does not exist!");
		return nullptr;
	}
	parts.erase(parts.begin());
	cmp->Load(parts);
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
	if (std::getline(file, line)) {
		entity = new Entity(line);
	}
	while (std::getline(file, line)) {
		if (line[0] == '\t') {
			line.erase(line.begin());
			AddStringComponentToEntity(entity, line);
		}
		else {
			system.AddEntity(entity);
			entity = new Entity(line);
		}
	}
	if (entity) {
		system.AddEntity(entity);
	}
}
