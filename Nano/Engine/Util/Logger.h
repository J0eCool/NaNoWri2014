#pragma once

#include <string>
#include <iostream>

#include <Windows.h>

inline void Log() {
	std::cout << std::endl;
	OutputDebugString("\n");
}

template <typename ... Ts>
inline void Log(std::string const& str, Ts ... rest) {
	std::cout << str;
	OutputDebugString(str.c_str());
	Log(rest...);
}
