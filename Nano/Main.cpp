#include <SDL.h>
#include <string>

#include "Logger.h"
#include "Managers/InputManager.h"

const int kScreenWidth = 800;
const int kScreenHeight = 600;

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
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
	if (!renderer)
	{
		Log("Renderer could not be created! SDL_Error: ", SDL_GetError());
		return 3;
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	SDL_Surface *screen = SDL_GetWindowSurface(window);
	SDL_Rect rect;
	rect.x = 190;
	rect.y = 75;
	rect.w = 50;
	rect.h = 69;

	bool quit = false;

	static const float kMaxFramerate = 60.0f;
	static const Uint32 kMaxFrameDelay = (Uint32)(1000.0f / kMaxFramerate);

	auto lastFrameTime = SDL_GetTicks();
	float t = 0.0f;
	float yPos = 120.0f;
	while (!quit)
	{
		float dT = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
		lastFrameTime = SDL_GetTicks();
		t += dT;

		InputManager::getInstance()->Update();
		quit = InputManager::getInstance()->IsDown(IN_Quit);

		// Logic
		yPos = 180.0f + sin(2.5f * t) * 300.0f;
		rect.y = (int)yPos;

		// Rendering
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0xff, 0x30, 0x30, 0x8f);
		SDL_RenderFillRect(renderer, &rect);

		SDL_RenderPresent(renderer);

		// Sleep until next frame
		auto elapsed = SDL_GetTicks() - lastFrameTime;
		auto delayTime = kMaxFrameDelay - elapsed;
		if (delayTime > 0) {
			// WTF: this causes the game to crashhang sometimes?
			//SDL_Delay(delayTime);
		}
	}

	Log("Well that went okay.", "I guess", "gosh");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
