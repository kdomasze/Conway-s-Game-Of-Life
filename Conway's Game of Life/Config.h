#pragma once
#include <string>
#include <vector>

class Config
{
	public:
		Config();
		Config(std::string fileName);
		~Config();

		int GetgridsX();
		int GetgridsY();

		std::vector<std::vector<bool>> getGridLayout();

	private:
		int gridsX;
		int gridsY;

		std::vector<std::vector<bool>> gridLayout;
};

