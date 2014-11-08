#include "Sprite.h"

#include <Nano/Managers/AssetManager.h>

//Sprite::Sprite(std::string imageName, SDL_Renderer *renderer) {
//	AssetManager *assets = AssetManager::GetInstance();
//	SDL_Surface *surface = assets->LoadSurface(imageName);
//	_width = surface->w;
//	_height = surface->h;
//	
//	_texture = assets->ConvertSurface(surface, renderer);
//
//	// XXX: This is wrong! If SDL_Surfaces get used through AssetManager things break.
//	// TODO: move Sprite into a higher-level collection, add LoadSprite method to AssetManager
//	assets->UnloadSurface(surface);
//}

SDL_Texture* Sprite::GetTexture() const {
	return _texture;
}

SDL_Rect Sprite::GetRect() const {
	SDL_Rect rect;
	rect.w = _width;
	rect.h = _height;
	return rect;
}

