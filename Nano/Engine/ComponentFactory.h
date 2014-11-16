#pragma once

#include <vector>
#include <string>

class Component;
class Entity;
class EntitySystem;

Component* CreateComponentFromStringArray(std::vector<std::string> parts);
Component* CreateComponentFromString(std::string string);
void AddStringComponentToEntity(Entity *entity, std::string str);
Entity* CreateEntityFromString(std::string string);
void AddEntitiesFromFile(EntitySystem& system, std::string filename);
