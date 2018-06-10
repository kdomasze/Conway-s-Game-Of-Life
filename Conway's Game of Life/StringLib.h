#pragma once
#include <vector>
#include <string>

namespace stringlib
{
	inline std::vector<std::string> split(std::string input, std::string delimiter)
	{
		size_t pos = 0;
		std::vector<std::string> split;

		while ((pos = input.find(delimiter)) != std::string::npos)
		{
			split.push_back(input.substr(0, pos));
			input.erase(0, pos + delimiter.length());
		}

		split.push_back(input);

		return split;
	}
}