#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#include "Managers/ManagerManager.h"
#include "Managers/InputManager.h"
#include "Constants.h"

#include "Engine/Engine.h"

#include "Engine/ComponentFactory.h"
#include "NanoEntityConfig.h"

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
		Log("SDL could not initialize! SDL_Error: ", SDL_GetError());
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("NaNo",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN);
	if (!window) {
		Log("Window could not be created! SDL_Error: ", SDL_GetError());
		return 2;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		Log("Renderer could not be created! SDL_Error: ", SDL_GetError());
		return 3;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		Log("SDL_image could not be initialized! SDL_Error: ", SDL_GetError(),
			" , IMG_Error: ", IMG_GetError());
		return 4;
	}

	if (TTF_Init() == -1) {
		Log("SDL_ttf could not be initialized! SDL_Error: ", SDL_GetError(),
			" , TTF_Error: ", TTF_GetError());
		return 5;
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_Surface *screen = SDL_GetWindowSurface(window);

	ManagerManager::GetInstance()->Init();

	NanoEntityConfig config;
	config.renderer = renderer;
	EntitySystem entitySystem(&config);
	AddEntitiesFromFile(entitySystem, "../Assets/Levels/Main.lvl");

	static const float kMaxFramerate = 120.0f;
	static const Uint32 kMaxFrameDelay = (Uint32)(1000.0f / kMaxFramerate);

	SDL_Texture *textTexture = nullptr;

	auto lastFrameTime = SDL_GetTicks();
	while (!InputManager::GetInstance()->IsDown(IT_Quit)) {
		float dt = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
		lastFrameTime = SDL_GetTicks();

		// Logic
		ManagerManager::GetInstance()->Update(dt);
		entitySystem.Update(dt);

		// Rendering
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(renderer);

		entitySystem.Draw();

		SDL_RenderPresent(renderer);

		// Sleep until next frame
		int elapsed = SDL_GetTicks() - lastFrameTime;
		int delayTime = kMaxFrameDelay - elapsed;
		if (delayTime > 0) {
			SDL_Delay(delayTime);
		}
	}

	ManagerManager::GetInstance()->Deinit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}
