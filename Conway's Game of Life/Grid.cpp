#include "Grid.h"
#include <SFML/Graphics/RectangleShape.hpp>

Grid::Grid(int winSize, int gridSize)
{
	windowSize = winSize;
	gridBoxSize = gridSize;
	windowGridFactor = windowSize / gridBoxSize;

	Grid::InitializeGrids();
	Grid::GenerateGridLines();
}

Grid::~Grid()
{
	FreeGrid(grid, windowGridFactor);
	FreeGrid(aliveGrid, windowGridFactor);

	// free the grid lines array
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < windowGridFactor; j++)
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


void Grid::Update()
{
	int dimensions = windowGridFactor;

	for (int x = 0; x < dimensions; x++)
	{
		for (int y = 0; y < dimensions; y++)
		{
			aliveGrid[x][y] = grid[x][y];
		}
	}

	StepThroughGrid();
}


void Grid::Draw(sf::RenderWindow& window)
{
	// draws grids
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < windowGridFactor; j++)
		{
			window.draw(gridLines[i][j], 2, sf::Lines);
		}
	}

	// draws cell fills
	sf::Vector2f size(gridBoxSize, gridBoxSize);

	for (int x = 0; x < windowGridFactor; x++)
	{
		for (int y = 0; y < windowGridFactor; y++)
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


void Grid::InitializeGrids()
{
	grid = new bool*[windowGridFactor];

	for (int x = 0; x < windowGridFactor; x++)
	{
		grid[x] = new bool[windowGridFactor];
		for (int y = 0; y < windowGridFactor; y++)
		{
			grid[x][y] = 0;
		}
	}

	aliveGrid = new bool*[windowGridFactor];

	for (int x = 0; x < windowGridFactor; x++)
	{
		aliveGrid[x] = new bool[windowGridFactor];
		for (int y = 0; y < windowGridFactor; y++)
		{
			aliveGrid[x][y] = 0;
		}
	}
}


void Grid::GenerateGridLines()
{
	gridLines = new sf::Vertex**[2];

	for (int i = 0; i < 2; i++)
	{
		gridLines[i] = new sf::Vertex*[windowGridFactor];
		for (int j = 0; j < windowGridFactor; j++)
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


void Grid::FreeGrid(bool **grid, int size)
{
	for (int i = 0; i < size; i++)
	{
		delete[] grid[i];
	}
	delete[] grid;
}


void Grid::StepThroughGrid()
{
	for (int x = 0; x < windowGridFactor; x++)
	{
		for (int y = 0; y < windowGridFactor; y++)
		{
			int cellsAlive = GetAliveCells(x, y);

			UpdateCells(x, y, cellsAlive);
		}
	}
}


int Grid::GetAliveCells(int x, int y)
{
	int cellsAlive = 0;

	for (int xi = x - 1; xi <= x + 1; xi++)
	{
		for (int yi = y - 1; yi <= y + 1; yi++)
		{
			if (!(xi < 0 || yi < 0 || xi >= windowGridFactor || yi >= windowGridFactor))
			{
				if (aliveGrid[xi][yi] && !(xi == x && yi == y))
				{
					cellsAlive++;
				}
			}
		}
	}

	return cellsAlive;
}


void Grid::UpdateCells(int x, int y, int cellsAlive)
{
	if (aliveGrid[x][y])
	{
		if (cellsAlive < 2 || cellsAlive > 3)
		{
			grid[x][y] = false;
		}
	}
	else
	{
		if (cellsAlive == 3)
		{
			grid[x][y] = true;
		}
	}
}