#include "Grid.h"
#include <SFML/Graphics/RectangleShape.hpp>


Grid::Grid(int gridSize, int window_size)
{
	size = gridSize;

	grid = new bool*[size];

	for (int x = 0; x < size; x++)
	{
		grid[x] = new bool[size];
		for (int y = 0; y < size; y++)
		{
			grid[x][y] = false;
		}
	}

	windowSize = window_size;
	gridPixelSize = windowSize / size;
	GenerateGridLines();
}


Grid::~Grid()
{
	for (int i = 0; i < size; i++)
	{
		delete[] grid[i];
	}
	delete[] grid;
}

Grid *Grid::Clone()
{
	Grid *gridClone = new Grid(size, windowSize);

	for(int x = 0; x < size; x++)
	{
		for(int y = 0; y < size; y++)
		{
			gridClone->SetStateAt(x, y, this->GetStateAt(x, y));
		}
	}

	return gridClone;
}


bool Grid::GetStateAt(int x, int y)
{
	return grid[x][y];
}


void Grid::SetStateAt(int x, int y, bool value)
{
	grid[x][y] = value;
}


void Grid::RandomizeState()
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			grid[x][y] = rand() % 2;
		}
	}
}


int Grid::GetSize()
{
	return size;
}


void Grid::Draw(sf::RenderWindow & window)
{
	// draws grids
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < size; j++)
		{
			window.draw(gridLines[i][j], 2, sf::Lines);
		}
	}

	// draws cell fills
	sf::Vector2f rectSize(gridPixelSize, gridPixelSize);

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (grid[x][y])
			{
				sf::RectangleShape cell(rectSize);
				cell.setPosition(x * gridPixelSize, y * gridPixelSize);

				window.draw(cell);
			}
		}
	}
}


void Grid::GenerateGridLines()
{
	gridLines = new sf::Vertex**[2];


	for (int i = 0; i < 2; i++)
	{
		gridLines[i] = new sf::Vertex*[size];
		for (int j = 0; j < size; j++)
		{
			gridLines[i][j] = new sf::Vertex[2];
			for (int k = 0; k < 2; k++)
			{
				int second = (k == 0) ? 0 : windowSize;
				if (i == 0)
				{
					gridLines[i][j][k] = sf::Vertex(sf::Vector2f(j * gridPixelSize, second));
				}
				else
				{
					gridLines[i][j][k] = sf::Vertex(sf::Vector2f(second, j * gridPixelSize));
				}
			}
		}
	}
}