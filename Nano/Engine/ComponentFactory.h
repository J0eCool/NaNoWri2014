#pragma once

#include <Nano/Generated/ComponentEnums.h>

#include <string>
#include <vector>

std::vector<std::string> SplitString(std::string string, char delim = ' ') {
	std::vector<std::string> list;
	std::string str = "";
	for (unsigned i = 0; i < string.length(); ++i) {
		char c = string[i];
		if (c == delim) {
			list.push_back(str);
			str = "";
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

Component* CreateComponentFromString(std::string string) {
	auto parts = SplitString(string);
	Component* cmp = CreateComponentWithName(parts[0]);
	parts.erase(parts.begin());
	cmp->Load(parts);
	return cmp;
}
