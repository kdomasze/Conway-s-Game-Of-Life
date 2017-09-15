#pragma once
#include <SFML/Graphics/Vertex.hpp>

class main
{
public:
	main();
	~main();

private:
	sf::Vertex[][][] CalculateGrid(int windowSize, int gridBoxSize);
};

