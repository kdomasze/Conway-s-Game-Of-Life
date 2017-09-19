#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class Grid
{
public:
	Grid(int size, int windowSize);
	~Grid();
	Grid *Clone();

	bool GetStateAt(int x, int y);
	void SetStateAt(int x, int y, bool value);
	int GetSize();

	void Draw(sf::RenderWindow& window);

private:
	bool **grid;
	int size;

	sf::Vertex ***gridLines;
	int gridPixelSize;
	int windowSize;

	void GenerateGridLines();
};

