#pragma once

#include "Util/Util.h"

class Component;
class Entity;
class EntitySystem;

Component* CreateComponentFromStringArray(Vector<String> parts);
Component* CreateComponentFromString(String string);
void AddStringComponentToEntity(Entity *entity, String str);
Entity* CreateEntityFromString(String string);
void AddEntitiesFromFile(EntitySystem& system, String filename);
