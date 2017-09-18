#include "Grid.h"
#include <SFML/Graphics/RectangleShape.hpp>

Grid::Grid(int winSize, int gridSize)
{
	windowSize = winSize;
	gridBoxSize = gridSize;

	Grid::InitializeGrid();
	Grid::GenerateGridLines();
}


Grid::~Grid()
{
	// free the grid data array
	for (int i = 0; i < windowSize / gridBoxSize; i++)
	{
		delete[] grid[i];
	}
	delete[] grid;

	// free the grid lines array
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < windowSize / gridBoxSize; j++)
		{
			delete[] gridLines[i][j];
		}
		delete[] gridLines[i];
	}
	delete[] gridLines;
}


void Grid::ToggleGridCell(sf::Vector2i localMousePosition)
{
	float x = localMousePosition.x;
	float y = localMousePosition.y;

	int gridXPos = floor(x / gridBoxSize);
	int gridYPos = floor(y / gridBoxSize);

	grid[gridXPos][gridYPos] = !grid[gridXPos][gridYPos];
}


void Grid::Draw(sf::RenderWindow& window)
{
	// draws grids
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < windowSize / gridBoxSize; j++)
		{
			window.draw(gridLines[i][j], 2, sf::Lines);
		}
	}

	// draws cell fills
	sf::Vector2f size(gridBoxSize, gridBoxSize);

	for (int x = 0; x < windowSize / gridBoxSize; x++)
	{
		for (int y = 0; y < windowSize / gridBoxSize; y++)
		{
			if(grid[x][y])
			{
				sf::RectangleShape cell(size);
				cell.setPosition(x * gridBoxSize, y * gridBoxSize);

				window.draw(cell);
			}
		}
	}
}


void Grid::InitializeGrid()
{
	grid = new bool*[windowSize / gridBoxSize];

	for (int x = 0; x < windowSize / gridBoxSize; x++)
	{
		grid[x] = new bool[windowSize / gridBoxSize];
		for (int y = 0; y < windowSize / gridBoxSize; y++)
		{
			grid[x][y] = 0;
		}
	}
}


void Grid::GenerateGridLines()
{
	gridLines = new sf::Vertex**[2];

	for (int i = 0; i < 2; i++)
	{
		gridLines[i] = new sf::Vertex*[windowSize / gridBoxSize];
		for (int j = 0; j < windowSize / gridBoxSize; j++)
		{
			gridLines[i][j] = new sf::Vertex[2];
			for (int k = 0; k < 2; k++)
			{
				int second = (k == 0) ? 0 : windowSize;
				if (i == 0)
				{
					gridLines[i][j][k] = sf::Vertex(sf::Vector2f(j * gridBoxSize, second));
				}
				else
				{
					gridLines[i][j][k] = sf::Vertex(sf::Vector2f(second, j * gridBoxSize));
				}
			}
		}
	}
}

