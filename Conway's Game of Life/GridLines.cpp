#include "GridLines.h"


GridLines::GridLines(int winSize, int gridSize)
{
	windowSize = winSize;
	gridBoxSize = gridSize;

	GridLines::CalculateGrid();
}


GridLines::~GridLines()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < windowSize / gridBoxSize; j++)
		{
			delete[] grid[i][j];
		}
		delete[] grid[i];
	}
	delete[] grid;
}


void GridLines::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < windowSize / gridBoxSize; j++)
		{
			window.draw(grid[i][j], 2, sf::Lines);
		}
	}
}


void GridLines::CalculateGrid()
{
	grid = new sf::Vertex**[2];

	for (int i = 0; i < 2; i++)
	{
		grid[i] = new sf::Vertex*[windowSize / gridBoxSize];
		for (int j = 0; j < windowSize / gridBoxSize; j++)
		{
			grid[i][j] = new sf::Vertex[2];
			for (int k = 0; k < 2; k++)
			{
				int second = (k == 0) ? 0 : windowSize;
				if (i == 0)
				{
					grid[i][j][k] = sf::Vertex(sf::Vector2f(j * gridBoxSize, second));
				}
				else
				{
					grid[i][j][k] = sf::Vertex(sf::Vector2f(second, j * gridBoxSize));
				}
			}
		}
	}
}

