#include "AssetManager.h"

#include <SDL_image.h>

#include "../Util/Logger.h"

std::string AssetManager::getFullImageFilename(std::string imageName) {
	return "../Assets/Textures/" + imageName + ".png";
}

std::string AssetManager::getFullFontFilename(std::string fontName) {
	return "../Assets/Fonts/" + fontName + ".ttf";
}

void AssetManager::Init() {
}

void AssetManager::Deinit() {
	for (auto it = _loadedTextures.begin(); it != _loadedTextures.end(); ++it) {
		SDL_DestroyTexture(it->second);
	}

	for (auto it = _loadedFonts.begin(); it != _loadedFonts.end(); ++it) {
		TTF_CloseFont(it->second);
	}
}

SDL_Texture *AssetManager::loadTexture(std::string imageName, SDL_Renderer *renderer) {
	if (!_loadedTextures[imageName]) {
		std::string filename = getFullImageFilename(imageName);
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

		_loadedTextures[imageName] = texture;
	}
	return _loadedTextures[imageName];
}

TTF_Font *AssetManager::loadFont(std::string fontName, int fontSize) {
	auto key = std::make_pair(fontName, fontSize);
	if (!_loadedFonts[key]) {
		std::string filename = getFullFontFilename(fontName);
		_loadedFonts[key] = TTF_OpenFont(filename.c_str(), fontSize);
	}
	return _loadedFonts[key];
}
