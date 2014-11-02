#include <SDL.h>
#include <string>

#include "Util/Logger.h"
#include "Util/Math.h"
#include "Managers/InputManager.h"

#include "Vec2.h"

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
	rect.x = 0;
	rect.y = kScreenHeight - 100;
	rect.w = kScreenWidth;
	rect.h = 50;

	SDL_Rect player;
	player.w = 50;
	player.h = 70;

	static const float kMaxFramerate = 60.0f;
	static const Uint32 kMaxFrameDelay = (Uint32)(1000.0f / kMaxFramerate);

	auto lastFrameTime = SDL_GetTicks();
	float t = 0.0f;
	Vec2 pos(200.0f, 120.0f);
	Vec2 vel;
	float speed = 225.0f;
	float gravity = 1000.0f;
	bool onGround = false;
	InputManager *input = InputManager::GetInstance();
	while (!input->IsDown(IT_Quit))
	{
		float dT = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
		lastFrameTime = SDL_GetTicks();
		t += dT;

		input->Update();

		// Logic
		vel.x = 0.0f;
		if (input->IsHeld(IT_Left)) {
			vel.x -= speed;
		}
		if (input->IsHeld(IT_Right)) {
			vel.x += speed;
		}
		if (!onGround) {
			vel.y += gravity * dT;
			if (pos.y + vel.y * dT + player.h > kScreenHeight - 100) {
				pos.y = kScreenHeight - 100 - (float)player.h;
				vel.y = 0.0f;
				onGround = true;
			}
		}
		else {
			if (input->IsDown(IT_Jump)) {
				vel.y = -0.5f * gravity;
				onGround = false;
			}
		}
		pos += vel * dT;
		pos.x = clamp(pos.x, 0, (float)(kScreenWidth - player.w));
		player.x = (int)pos.x;
		player.y = (int)pos.y;

		// Rendering
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0xff, 0x80, 0x80, 0xff);
		SDL_RenderFillRect(renderer, &player);

		SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xff);
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
