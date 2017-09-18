#pragma once
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace sf {
	class RenderWindow;
}

class Grid
{
public:
	Grid(int winSize, int gridSize);
	~Grid();

	void ToggleGridCell(sf::Vector2i localMousePosition);
	void Draw(sf::RenderWindow& window);

private:
	sf::Vertex ***gridLines;

	bool **grid;

	int windowSize;
	int gridBoxSize;

	void InitializeGrid();
	void GenerateGridLines();
};

