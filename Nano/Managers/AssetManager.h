#pragma once

#include "Singleton.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <Nano/Engine/Util/Util.h>
#include <Nano/Sprite.h>

class AssetManager : public Singleton<AssetManager> {
private:
	Dict<String, SDL_Surface*> _loadedSurfaces;
	Dict<String, SDL_Texture*> _loadedTextures;
	Dict<String, Sprite*> _loadedSprites;
	Dict<Pair<String, int>, TTF_Font*> _loadedFonts;

	String getFullImageFilename(String imageName);
	String getFullFontFilename(String fontName);

public:
	void Init();
	void Deinit();

	SDL_Surface* LoadSurface(String imageName);
	SDL_Texture* ConvertSurface(SDL_Surface *surface, SDL_Renderer *renderer);
	SDL_Texture* LoadTexture(String imageName, SDL_Renderer *renderer);
	TTF_Font *LoadFont(String fontName, int fontSize);
	Sprite LoadSprite(String spriteName, SDL_Renderer *renderer);

	void UnloadSurface(SDL_Surface *surface);
	void UnloadTexture(SDL_Texture *texture);
	void UnloadFont(TTF_Font *font);
};
