#include "ComponentFactory.h"

#include "Util/Util.h"

#include "Component.h"
#include "Entity.h"
#include "EntitySystem.h"

Vector<Vector<String>> SplitLinesOnTabs(Vector<String> const& rawLines, int tabCount) {
	Vector<Vector<String>> groups;
	Vector<String> currentGroup;
	for (unsigned i = 0; i < rawLines.size(); ++i) {
		String line = rawLines[i];
		if (TabCount(line) <= tabCount) {
			if (currentGroup.size() > 0) {
				groups.push_back(currentGroup);
			}
			currentGroup.clear();
		}
		currentGroup.push_back(line);
	}
	if (currentGroup.size() > 0) {
		groups.push_back(currentGroup);
	}
	return groups;
}

Component* ParseComponent(Vector<String>& lines) {
	String name = Trim(lines[0]);
	Component* component = CreateComponentWithName(name);
	component->_type = GetComponentType(name);
	for (unsigned i = 1; i < lines.size(); ++i) {
		auto line = Trim(lines[i]);
		auto kv = SplitString(line, ':');
		component->LoadArg(Trim(kv[0]), Trim(kv[1]));
	}
	return component;
}

Entity* ParseEntity(String const& name, Vector<String>& lines, int componentTabs) {
	Entity* entity = new Entity(name);
	auto componentLines = SplitLinesOnTabs(lines, componentTabs);
	for (auto group : componentLines) {
		Component *component = ParseComponent(group);
		entity->AddComponent(component);
	}
	return entity;
}

Entity* ParseEntity(Vector<String>& lines) {
	String name = Trim(lines[0]);
	lines.erase(lines.begin());
	return ParseEntity(name, lines, 1);
}

Entity* LoadPrefabFromFile(String const& filename) {
	auto rawLines = ReadLinesFromFile(filename);
	int index = filename.find_last_of(".");
	String name = filename.substr(0, index);
	return ParseEntity(name, rawLines, 0);
}

void AddEntitiesFromFile(EntitySystem& system, String const& filename) {
	auto rawLines = ReadLinesFromFile(filename);
	auto entityLines = SplitLinesOnTabs(rawLines, 0);
	for (auto group : entityLines) {
		Entity *ent = ParseEntity(group);
		system.AddEntity(ent);
	}
}
