#pragma once

#include "Util/Util.h"

class Component;
class Entity;
class EntitySystem;

Entity* LoadPrefabFromFile(String const& filename);
void AddEntitiesFromFile(EntitySystem& system, String const& filename);
