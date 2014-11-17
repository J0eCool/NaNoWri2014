#include "StringHandling.h"

std::vector<std::string> SplitString(std::string string, char delim) {
	std::vector<std::string> list;
	std::string str = "";
	for (unsigned i = 0; i < string.length(); ++i) {
		char c = string[i];
		if (c == delim) {
			if (str.length() > 0) {
				list.push_back(str);
				str = "";
			}
		}
		else {
			str += c;
		}
	}
	if (str.length() > 0) {
		list.push_back(str);
	}
	return list;
}

std::string TrimRight(std::string str, std::string trimChars) {
	auto end = str.find_last_not_of(trimChars.c_str());
	if (end != std::string::npos) {
		return str.substr(0, end + 1);
	}
	return str;
}

int ParseInt(std::string const& str) {
	// Parse int as hex if string starts with "0x"
	if (str.length() > 2 && str[0] == '0' && str[1] == 'x') {
		return (int)strtol(str.c_str(), nullptr, 16);
	}
	return atoi(str.c_str());
}

float ParseFloat(std::string const& str) {
	return (float)atof(str.c_str());
}

std::string ParseString(std::string const& str) {
	return str;
}

Vec2 ParseVec2(std::string const& str) {
	auto parts = SplitString(str, ',');
	float x = ParseFloat(parts[0]);
	float y = ParseFloat(parts[1]);
	return Vec2(x, y);
}

SDL_Color ParseColor(std::string const& str) {
	auto parts = SplitString(str, ',');
	int r = ParseInt(parts[0]);
	int g = ParseInt(parts[1]);
	int b = ParseInt(parts[2]);
	int a = parts.size() > 3 ? ParseInt(parts[3]) : 0xff;
	return { r, g, b, a };
}
