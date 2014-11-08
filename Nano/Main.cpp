#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#include "Managers/AssetManager.h"
#include "Managers/InputManager.h"
#include "Constants.h"

#include "Engine/Engine.h"

#include "Components/Components.h"

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

	InputManager *input = InputManager::GetInstance();
	input->Init();
	AssetManager *asset = AssetManager::GetInstance();
	asset->Init();

	EntitySystem entitySystem;

	// ground
	entitySystem.AddEntity(new Entity{
		new Transform({ 0, (float)kScreenHeight - 100 }, { (float)kScreenWidth, 50 }),
		(new Renderer(renderer))->SetColor({ 0x80, 0xa0, 0x80, 0xff }),
		new Collider,
	});

	// lower platform
	entitySystem.AddEntity(new Entity{
		(new Renderer(renderer))->SetColor({ 0xd0, 0xc0, 0x20, 0xff }),
		new Collider,
		new Transform({ 400, 360 }, { 160, 48 })
	});

	// middle platform
	entitySystem.AddEntity(new Entity{
		(new Renderer(renderer))->SetColor({ 0xc0, 0xd0, 0x20, 0xff }),
		new Collider,
		new Transform({ 150, 240 }, { 160, 48 })
	});

	// higher platform
	entitySystem.AddEntity(new Entity{
		(new Renderer(renderer))->SetColor({ 0xb0, 0xf0, 0x20, 0xff }),
		new Collider,
		new Transform({ 540, 140 }, { 160, 48 })
	});

	Entity *player = new Entity{
		new Player,
		new Transform({ 120.0f, 200.0f }, { 50.0f, 70.0f }),
		new Collider,
		(new Renderer(renderer))->SetColor({ 0x20, 0xc0, 0xff, 0xff })
	};
	entitySystem.AddEntity(player);

	Entity *playerPosText = new Entity{
		new TextRenderer(asset->loadFont("arial", 32), renderer),
		new Transform({ 50, 50 }, { 0, 0 }),
	};
	entitySystem.AddEntity(playerPosText);

	SDL_Texture *tex = asset->loadTexture("Sigma", renderer);
	
	SDL_Rect sig;
	sig.x = kScreenWidth - 80;
	sig.y = 30;
	sig.w = 50;
	sig.h = 50;

	SDL_Rect textRect;
	textRect.x = 50;
	textRect.y = 50;

	static const float kMaxFramerate = 60.0f;
	static const Uint32 kMaxFrameDelay = (Uint32)(1000.0f / kMaxFramerate);

	SDL_Texture *textTexture = nullptr;

	auto lastFrameTime = SDL_GetTicks();
	float t = 0.0f;
	while (!input->IsDown(IT_Quit)) {
		float dt = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
		t += dt;
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

		SDL_SetTextureColorMod(tex, lerp(sin(t) / 2 + 0.5f, 0x00, 0xff), 0xff, 0xff);
		SDL_RenderCopyEx(renderer, tex, nullptr, &sig, 80 * t, nullptr, SDL_FLIP_NONE);

		SDL_RenderPresent(renderer);

		// Sleep until next frame
		auto elapsed = SDL_GetTicks() - lastFrameTime;
		auto delayTime = kMaxFrameDelay - elapsed;
		if (delayTime > 0) {
			// WTF: this causes the game to crashhang sometimes?
			//SDL_Delay(delayTime);
		}
	}

	asset->Deinit();
	input->Deinit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}
