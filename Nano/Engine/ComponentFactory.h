#pragma once

#include <Nano/Generated/ComponentEnums.h>
#include <Nano/Engine/Engine.h>
#include "Util/StringHandling.h"

#include "Util/Util.h"

#include <string>

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
