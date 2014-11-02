#pragma once

#include <string>
#include <iostream>

#include <Windows.h>

void Log()
{
	std::cout << std::endl;
	OutputDebugString("\n");
}

template <typename ... Ts>
void Log(std::string const& str, Ts ... rest)
{
	std::cout << str;
	OutputDebugString(str.c_str());
	Log(rest...);
}
