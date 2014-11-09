#pragma once

#include <string>
#include <vector>

std::vector<std::string> SplitString(std::string string, char delim = ' ');

int ParseInt(std::string const& str);
float ParseFloat(std::string const& str);
