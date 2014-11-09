#pragma once

#include <SDL.h>

#include <Nano/Engine/EntitySystem.h>

class NanoEntityConfig : public EntityConfig {
public:
	SDL_Renderer *renderer;
};
