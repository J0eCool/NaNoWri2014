#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "Managers/InputManager.h"
#include "Util/Constants.h"
#include "Util/Logger.h"
#include "Util/Math.h"
#include "Util/Vec2.h"

#include "Player.h"

SDL_Texture *loadImage(std::string filename, SDL_Renderer *renderer) {
	SDL_Surface *loadedSurface = IMG_Load(filename.c_str());
	if (!loadedSurface) {
		Log("Image could not be loaded! Filename: \"", filename, "\" SDL_Error: ", SDL_GetError());
		return nullptr;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);
	if (!texture) {
		Log("Surface could not be converted! Filename: \"", filename, "\" SDL_Error: ", SDL_GetError());
		return nullptr;
	}

	return texture;
}

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
		Log("Image loading could not be initialized! SDL_Error: ", SDL_GetError());
		return 4;
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	SDL_Surface *screen = SDL_GetWindowSurface(window);
	SDL_Rect rect;
	rect.x = 0;
	rect.y = kScreenHeight - 100;
	rect.w = kScreenWidth;
	rect.h = 50;

	SDL_Rect sig;
	sig.x = kScreenWidth - 80;
	sig.y = 30;
	sig.w = 50;
	sig.h = 50;

	static const float kMaxFramerate = 60.0f;
	static const Uint32 kMaxFrameDelay = (Uint32)(1000.0f / kMaxFramerate);

	Player player(Vec2(50.0f, 70.0f), Vec2(200.0f, 360.0f));

	SDL_Texture *tex = loadImage("../Assets/Textures/Sigma.png", renderer);

	InputManager *input = InputManager::GetInstance();
	input->Init();

	auto lastFrameTime = SDL_GetTicks();
	float t = 0.0f;
	while (!input->IsDown(IT_Quit))
	{
		float dt = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
		t += dt;
		lastFrameTime = SDL_GetTicks();

		input->Update();

		// Logic
		player.Update(dt);

		// Rendering
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(renderer);

		player.Draw(renderer);

		SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xff);
		SDL_RenderFillRect(renderer, &rect);

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

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
