#pragma once

#include <string>
#include <sstream>
#include <iostream>

#include <Windows.h>

#ifdef SendMessage
#undef SendMessage
#endif

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

template <typename T, typename ... Ts>
inline void Log(T item, Ts ... rest) {
	std::stringstream sstr;
	sstr << item;

	std::cout << sstr.str();
	OutputDebugString(sstr.str().c_str());
	Log(rest...);
}
