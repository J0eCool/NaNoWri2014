#include "AssetManager.h"

#include <SDL_image.h>

#include <Nano/Engine/Engine.h>

// TODO: asset build step to copy assets into a sensible location
String AssetManager::getFullImageFilename(String imageName) {
	return "../Assets/Textures/" + imageName + ".png";
}

String AssetManager::getFullFontFilename(String fontName) {
	return "../Assets/Fonts/" + fontName + ".ttf";
}

void AssetManager::Init() {
}

template <typename C, typename F>
void unloadContainer(C container, F clearFunction) {
	for (auto it = container.begin(); it != container.end(); ++it) {
		clearFunction(it->second);
	}
}

void AssetManager::Deinit() {
	unloadContainer(_loadedSurfaces, SDL_FreeSurface);
	unloadContainer(_loadedTextures, SDL_DestroyTexture);
	unloadContainer(_loadedFonts, TTF_CloseFont);

	for (auto kv : _loadedSprites) {
		delete kv.second;
	}
}

SDL_Surface* AssetManager::LoadSurface(String imageName) {
	if (!_loadedSurfaces[imageName]) {
		String filename = getFullImageFilename(imageName);
		SDL_Surface *loadedSurface = IMG_Load(filename.c_str());
		if (!loadedSurface) {
			Log("Image could not be loaded! Filename: \"", filename, "\" SDL_Error: ", SDL_GetError());
			return nullptr;
		}
		_loadedSurfaces[imageName] = loadedSurface;
	}
	return _loadedSurfaces[imageName];
}

SDL_Texture* AssetManager::ConvertSurface(SDL_Surface *surface, SDL_Renderer *renderer) {
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		Log("Surface could not be converted! SDL_Error: ", SDL_GetError());
		return nullptr;
	}
	return texture;
}

SDL_Texture* AssetManager::LoadTexture(String imageName, SDL_Renderer *renderer) {
	if (!_loadedTextures[imageName]) {
		bool shouldUnload = _loadedSurfaces[imageName] == nullptr;
		SDL_Surface *surface = LoadSurface(imageName);
		if (!surface) {
			return nullptr;
		}

		SDL_Texture *texture = ConvertSurface(surface, renderer);
		if (shouldUnload) {
			UnloadSurface(surface);
		}
		if (!texture) {
			return nullptr;
		}

		_loadedTextures[imageName] = texture;
	}
	return _loadedTextures[imageName];
}

TTF_Font* AssetManager::LoadFont(String fontName, int fontSize) {
	auto key = std::make_pair(fontName, fontSize);
	if (!_loadedFonts[key]) {
		String filename = getFullFontFilename(fontName);
		_loadedFonts[key] = TTF_OpenFont(filename.c_str(), fontSize);
	}
	return _loadedFonts[key];
}

Sprite AssetManager::LoadSprite(String spriteName, SDL_Renderer *renderer) {
	if (!_loadedSprites[spriteName]) {
		bool shouldUnload = _loadedSurfaces[spriteName] == nullptr;
		SDL_Surface *surface = LoadSurface(spriteName);
		SDL_Texture *texture = LoadTexture(spriteName, renderer);

		Sprite *sprite = new Sprite;
		sprite->_texture = texture;
		sprite->_renderer = renderer;
		sprite->_width = surface->w;
		sprite->_height = surface->h;

		if (shouldUnload) {
			UnloadSurface(surface);
		}

		_loadedSprites[spriteName] = sprite;
	}
	return *_loadedSprites[spriteName];
}

template <typename T, typename C, typename F>
void unloadItem(T item, C& container, F freeCall) {
	for (auto it = container.begin(); it != container.end(); ++it) {
		if (it->second == item) {
			container.erase(it);
			break;
		}
	}
	freeCall(item);
}

void AssetManager::UnloadSurface(SDL_Surface *surface) {
	unloadItem(surface, _loadedSurfaces, SDL_FreeSurface);
}

void AssetManager::UnloadTexture(SDL_Texture *texture) {
	unloadItem(texture, _loadedTextures, SDL_DestroyTexture);
}

void AssetManager::UnloadFont(TTF_Font *font) {
	unloadItem(font, _loadedFonts, TTF_CloseFont);
}
