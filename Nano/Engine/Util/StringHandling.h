#pragma once

#include "Vec2.h"

#include <SDL.h>
#include <string>
#include <vector>

std::vector<std::string> SplitString(std::string const& string, char delim = ' ');

int TabCount(std::string const& str);
std::string TrimRight(std::string const& str, std::string const& trimChars = " \t");
std::string TrimLeft(std::string const& str, std::string const& trimChars = " \t");
std::string Trim(std::string const& str, std::string const& trimChars = " \t");

int ParseInt(std::string const& str);
float ParseFloat(std::string const& str);
std::string ParseString(std::string const& str);
Vec2 ParseVec2(std::string const& str);
SDL_Color ParseColor(std::string const& str);
