#include "Config.h"
#include "StringLib.h"
#include <iostream>
#include <fstream>

Config::Config()
{
}

Config::Config(std::string fileName)
{
	// default config is set in case file loading fails or no file loads
	std::vector<std::string> config = { "50x50", "null" };

	// if config is to be loaded, attempt to load it
	if (fileName != "null")
	{
		std::ifstream inFile;
		inFile.open(fileName);
		if (inFile)
		{
			config.clear();

			for (std::string line; std::getline(inFile, line);)
			{
				config.push_back(line);
			}
		}
	}

	// get grid params
	auto configParams = stringlib::split(config[0], "x");

	gridLayout = std::vector<std::vector<bool>>(this->gridsY);

	// check config params are valid
	if (configParams.size() != 2)
	{
		std::cerr << "Bad config: invalid parameters on line 1. Expected: \"#x#\"" << ", Actual: " << config[0] << std::endl;
		std::cin.get();
		exit(-1);
	}

	// remove params from config to leave only grid data
	config.erase(config.begin());

	this->gridsX = stoi(configParams[0]);
	this->gridsY = stoi(configParams[1]);

	// integrity checks:
	// if the number of rows does not equal 1 or the expected number of rows, error and exit
	if (config.size() != 1)
	{
		if (config.size() != gridsY)
		{
			std::cerr << "Bad config: Too many rows. Expected: " << gridsY << ", Actual: " << config.size() << std::endl;
			std::cin.get();
			exit(-3);
		}
	}
	// if the number of rows equals 1 and that row is null, prepare grid of param size with all cells empty
	else if (config.size() == 1)
	{
		if (config[0] == "null")
		{
			std::vector<bool> tmpGridLine(this->gridsX);

			for (int y = 0; y < this->gridsY; y++)
			{
				for (int x = 0; x < this->gridsX; x++)
				{
					tmpGridLine.push_back(false);
				}

				this->gridLayout.push_back(tmpGridLine);
				tmpGridLine.swap(std::vector<bool>(this->gridsX));
			}

			return;
		}
	}

	std::vector<bool> tmpGridLine(this->gridsX);

	// if all checks pass, start parsing grid data
	for (int y = 0; y < this->gridsY; y++)
	{
		for (int x = 0; x < this->gridsX; x++)
		{
			// if cell data is not 0 or 1, error and quit
			if (config[y][x] != '0' && config[y][x] != '1')
			{
				std::cerr << "Bad config: invalid character on line " << y + 2 << ". Expected: \"0\" or \"1\"" << ", Actual: " << config[y][x] << std::endl;
				std::cin.get();
				exit(-2);
			}

			if (config[y][x] == '0')
			{
				tmpGridLine.push_back(false);
			}
			else
			{
				tmpGridLine.push_back(true);
			}
		}

		this->gridLayout.push_back(tmpGridLine);
		tmpGridLine.swap(std::vector<bool>(this->gridsX));
	}
}

Config::~Config()
{
}

int Config::GetgridsX()
{
	return this->gridsX;
}

int Config::GetgridsY()
{
	return this->gridsY;
}

std::vector<std::vector<bool>> Config::getGridLayout()
{
	return this->gridLayout;
}
