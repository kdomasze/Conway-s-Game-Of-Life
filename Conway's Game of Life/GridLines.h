#pragma once
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace sf {
	class RenderWindow;
}

class GridLines
{
public:
	GridLines(int winSize, int gridSize);
	~GridLines();
	void Draw(sf::RenderWindow& window);

private:
	sf::Vertex ***grid;
	int windowSize;
	int gridBoxSize;
	void CalculateGrid();
};

