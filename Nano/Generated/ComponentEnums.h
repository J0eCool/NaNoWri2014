#pragma once

#include <string>
#include <map>
#include <Nano/Components/Components.h>

Component* CreateComponentWithName(std::string name) {
	if (name == "Collider") { return new Collider; }
	if (name == "Player") { return new Player; }
	if (name == "Renderer") { return new Renderer; }
	if (name == "SpriteRenderer") { return new SpriteRenderer; }
	if (name == "TextRenderer") { return new TextRenderer; }
	if (name == "SpinningSigma") { return new SpinningSigma; }
	return nullptr;
}

