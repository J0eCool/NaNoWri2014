#pragma once

#include "Singleton.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
#include <string>

class AssetManager : public Singleton<AssetManager> {
private:
	std::map<std::string, SDL_Texture*> _loadedTextures;
	std::map<std::pair<std::string, int>, TTF_Font*> _loadedFonts;

	std::string getFullImageFilename(std::string imageName);
	std::string getFullFontFilename(std::string fontName);

public:
	void Init();
	void Deinit();

	SDL_Texture *loadTexture(std::string imageName, SDL_Renderer *renderer);
	TTF_Font *loadFont(std::string fontName, int fontSize);
};
