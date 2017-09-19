#pragma once
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Grid
{
public:
	Grid(int winSize, int gridSize);
	~Grid();

	void ToggleGridCell(sf::Vector2i localMousePosition);
	void Update();
	void Draw(sf::RenderWindow& window);

private:
	sf::Vertex ***gridLines;
	bool **grid;
	bool **aliveGrid;

	int windowSize;
	int gridBoxSize;
	int windowGridFactor;

	void InitializeGrids();
	void GenerateGridLines();

	void FreeGrid(bool **grid, int size);
	void StepThroughGrid();
	int GetAliveCells(int x, int y);
	void UpdateCells(int x, int y, int cellsAlive);
};

