#include <SDL.h>
#include <string>

#include "Logger.h"

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
	SDL_Event event;

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

		// handle events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = true;
				}
				break;
			}
		}

		// logic
		yPos = 180.0f + sin(2.5f * t) * 300.0f;
		rect.y = (int)yPos;

		// rendering
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0xff, 0x30, 0x30, 0x8f);
		SDL_RenderFillRect(renderer, &rect);

		SDL_RenderPresent(renderer);

		// sleep until next frame
		auto elapsed = SDL_GetTicks() - lastFrameTime;
		auto delayTime = kMaxFrameDelay - elapsed;
		if (delayTime > 0)
		{
			SDL_Delay(delayTime);
		}
	}

	Log("Well that went okay.", "I guess", "gosh");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
