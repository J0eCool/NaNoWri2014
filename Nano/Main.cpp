#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#include "Managers/AssetManager.h"
#include "Managers/InputManager.h"
#include "Constants.h"

#include "Engine/Engine.h"

#include "Components/Components.h"

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

	InputManager::GetInstance()->Init();
	AssetManager::GetInstance()->Init();

	NanoEntityConfig config;
	config.renderer = renderer;
	EntitySystem entitySystem(&config);

	// ground
	entitySystem.AddEntity(CreateEntityFromString(
		"Transform 0 500 800 50\n"
		"Renderer 0x80 0xa0 0x80 0xff\n"
		"Collider\n"
	));

	// lower platform
	entitySystem.AddEntity(CreateEntityFromString(
		"Renderer 0xd0 0xc0 0x20 0xff\n"
		"Collider\n"
		"Transform 400 360 160 48\n"
	));

	// middle platform
	entitySystem.AddEntity(CreateEntityFromString(
		"Renderer 0xc0 0xd0 0x20 0xff\n"
		"Collider\n"
		"Transform 150 240 160 48\n"
	));

	// higher platform
	entitySystem.AddEntity(CreateEntityFromString(
		"Renderer 0xb0 0xf0 0x20 0xff\n"
		"Collider\n"
		"Transform 540 140 160 48\n"
	));

	Entity *player = CreateEntityFromString(
		"Player\n"
		"Transform 120.0f 200.0f 50.0f 70.0f\n"
		"Collider\n"
		"Renderer 0x20 0xc0 0xff 0xff\n"
	);
	entitySystem.AddEntity(player);

	Entity *playerPosText = CreateEntityFromString(
		"TextRenderer arial 24\n"
		"Transform 50 50 0 0\n"
	);
	entitySystem.AddEntity(playerPosText);

	entitySystem.AddEntity(CreateEntityFromString(
		"SpriteRenderer Sigma\n"
		"Transform 720 30 50 50\n"
		"SpinningSigma 150.0f 6.0f\n"
	));

	static const float kMaxFramerate = 120.0f;
	static const Uint32 kMaxFrameDelay = (Uint32)(1000.0f / kMaxFramerate);

	SDL_Texture *textTexture = nullptr;

	auto lastFrameTime = SDL_GetTicks();
	InputManager *input = InputManager::GetInstance();
	while (!input->IsDown(IT_Quit)) {
		float dt = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
		lastFrameTime = SDL_GetTicks();

		input->Update();

		// Logic
		std::string posText = player->GetTransform()->pos.ToString();
		playerPosText->GetComponent<TextRenderer>()->SetText(posText);
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

	AssetManager::GetInstance()->Deinit();
	InputManager::GetInstance()->Deinit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}
