#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class Grid
{
public:
	Grid(int gridX, int gridY, int windowSize);
	~Grid();
	Grid *Clone();

	bool GetStateAt(int x, int y);
	void SetStateAt(int x, int y, bool value);
	void SetStateForAll(std::vector<std::vector<bool>> gridLayout);
	void RandomizeState();

	int GetGridX();
	int GetGridY();

	void Draw(sf::RenderWindow& window);

private:
	bool **grid;
	int gridX;
	int gridY;

	sf::Vertex ***gridLines;
	int gridPixelSizeX;
	int gridPixelSizeY;
	int windowSize;

	void GenerateGridLines();
};

