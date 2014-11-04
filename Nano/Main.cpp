#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#include "Managers/AssetManager.h"
#include "Managers/InputManager.h"
#include "Util/Constants.h"
#include "Util/Logger.h"
#include "Util/Math.h"
#include "Util/Vec2.h"

#include "Engine/Entity.h"
#include "Engine/EntitySystem.h"
#include "Engine/Components/Player.h"
#include "Engine/Components/Renderer.h"
#include "Engine/Components/Transform.h"

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		Log("SDL could not initialize! SDL_Error: ", SDL_GetError());
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("NaNo",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN);
	if (!window)
	{
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
		(new Renderer(renderer))->SetColor({ 0x80, 0xa0, 0x80, 0xff })
	});
	
	Entity *player = new Entity{
		new Player,
		new Transform({ 120.0f, 200.0f }, { 50.0f, 70.0f }),
		(new Renderer(renderer))->SetColor({ 0x20, 0xc0, 0xff, 0xff })
	};
	entitySystem.AddEntity(player);

	entitySystem.AddEntity(new Entity{
		(new Renderer(renderer))->SetColor({ 0xd0, 0xc0, 0x20, 0xff }),
		new Transform({ 400, 160 }, { 100, 24 })
	});

	SDL_Texture *tex = asset->loadTexture("Sigma", renderer);
	TTF_Font *font = asset->loadFont("arial", 32);
	
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
	while (!input->IsDown(IT_Quit))
	{
		float dt = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
		t += dt;
		lastFrameTime = SDL_GetTicks();

		input->Update();

		// Logic
		entitySystem.Update(dt);

		// Rendering
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(renderer);

		entitySystem.Draw();

			SDL_DestroyTexture(textTexture);
			std::string text = player->GetComponent<Transform>()->pos.ToString();
			SDL_Surface *textSurf = TTF_RenderText_Solid(font, text.c_str(), { 0, 0, 0 });
			textRect.w = textSurf->w;
			textRect.h = textSurf->h;
			textTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
			SDL_FreeSurface(textSurf);

		SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

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
