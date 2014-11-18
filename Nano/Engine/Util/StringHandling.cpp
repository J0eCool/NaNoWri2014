#include "StringHandling.h"

Vector<String> SplitString(String const& string, char delim) {
	Vector<String> list;
	String str = "";
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

int TabCount(String const& line) {
	int count = 0;
	for (unsigned i = 0; i < line.length(); ++i) {
		if (line[i] == '\t') {
			count++;
		}
		else {
			break;
		}
	}
	return count;
}

String TrimRight(String const& str, String const& trimChars) {
	auto end = str.find_last_not_of(trimChars.c_str());
	if (end != String::npos) {
		return str.substr(0, end + 1);
	}
	return "";
}

String TrimLeft(String const& str, String const& trimChars) {
	auto start = str.find_first_not_of(trimChars.c_str());
	if (start != String::npos) {
		return str.substr(start, str.length());
	}
	return "";
}

String Trim(String const& str, String const& trimChars) {
	return TrimLeft(TrimRight(str, trimChars), trimChars);
}

int ParseInt(String const& str) {
	// Parse int as hex if string starts with "0x"
	if (str.length() > 2 && str[0] == '0' && str[1] == 'x') {
		return (int)strtol(str.c_str(), nullptr, 16);
	}
	return atoi(str.c_str());
}

float ParseFloat(String const& str) {
	return (float)atof(str.c_str());
}

String ParseString(String const& str) {
	return str;
}

Vec2 ParseVec2(String const& str) {
	auto parts = SplitString(str, ',');
	float x = ParseFloat(parts[0]);
	float y = ParseFloat(parts[1]);
	return Vec2(x, y);
}

SDL_Color ParseColor(String const& str) {
	auto parts = SplitString(str, ',');
	int r = ParseInt(parts[0]);
	int g = ParseInt(parts[1]);
	int b = ParseInt(parts[2]);
	int a = parts.size() > 3 ? ParseInt(parts[3]) : 0xff;
	return { r, g, b, a };
}
