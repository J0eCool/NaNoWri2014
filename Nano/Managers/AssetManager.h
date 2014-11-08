#pragma once

#include "Singleton.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
#include <string>

#include <Nano/Sprite.h>

class AssetManager : public Singleton<AssetManager> {
private:
	std::map<std::string, SDL_Surface*> _loadedSurfaces;
	std::map<std::string, SDL_Texture*> _loadedTextures;
	std::map<std::string, Sprite*> _loadedSprites;
	std::map<std::pair<std::string, int>, TTF_Font*> _loadedFonts;

	std::string getFullImageFilename(std::string imageName);
	std::string getFullFontFilename(std::string fontName);

public:
	void Init();
	void Deinit();

	SDL_Surface* LoadSurface(std::string imageName);
	SDL_Texture* ConvertSurface(SDL_Surface *surface, SDL_Renderer *renderer);
	SDL_Texture* LoadTexture(std::string imageName, SDL_Renderer *renderer);
	TTF_Font *LoadFont(std::string fontName, int fontSize);
	Sprite LoadSprite(std::string spriteName, SDL_Renderer *renderer);

	void UnloadSurface(SDL_Surface *surface);
	void UnloadTexture(SDL_Texture *texture);
	void UnloadFont(TTF_Font *font);
};
