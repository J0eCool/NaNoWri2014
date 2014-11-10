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
