#pragma once

#include "Containers.h"
#include "Vec2.h"

#include <SDL.h>

Vector<String> SplitString(String const& string, char delim = ' ');

int TabCount(String const& str);
String TrimRight(String const& str, String const& trimChars = " \t");
String TrimLeft(String const& str, String const& trimChars = " \t");
String Trim(String const& str, String const& trimChars = " \t");

int ParseInt(String const& str);
float ParseFloat(String const& str);
String ParseString(String const& str);
Vec2 ParseVec2(String const& str);
SDL_Color ParseColor(String const& str);
