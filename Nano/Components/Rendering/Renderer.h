#pragma once

#include <SDL.h>

#include <Nano/Engine/Engine.h>

class Camera;

class Renderer : public Component {
private:
	SDL_Renderer *_renderer;
	SDL_Color _color;
	Camera *_camera;

public:
	Renderer();
	//$$_color:Color
	void LoadArg(String const& key, String const& val) override;

	void Start() override;
	void Draw() override;

	Renderer* SetColor(SDL_Color color);
};
