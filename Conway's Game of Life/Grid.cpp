#include "Grid.h"
#include <SFML/Graphics/RectangleShape.hpp>


Grid::Grid(int gridX, int gridY, int window_size)
{
	this->gridX = gridX;
	this->gridY = gridY;

	grid = new bool*[gridX];

	for (int x = 0; x < this->gridX; x++)
	{
		grid[x] = new bool[gridY];
		for (int y = 0; y < this->gridY; y++)
		{
			grid[x][y] = false;
		}
	}

	windowSize = window_size;
	gridPixelSizeX = windowSize / this->gridX; 
	gridPixelSizeY = windowSize / this->gridY;
	GenerateGridLines();
}


Grid::~Grid()
{
	for (int i = 0; i < this->gridX; i++)
	{
		delete[] grid[i];
	}
	delete[] grid;
	
	for (int i = 0; i < this->gridX; i++)
	{
		delete[] gridLines[0][i];
	}

	for (int i = 0; i < this->gridY; i++)
	{
		delete[] gridLines[1][i];
	}

	delete[] gridLines[0];
	delete[] gridLines[1];

	delete[] gridLines;
}

Grid *Grid::Clone()
{
	Grid *gridClone = new Grid(this->gridX, this->gridY, windowSize);

	for(int x = 0; x < this->gridX; x++)
	{
		for(int y = 0; y < this->gridY; y++)
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

void Grid::SetStateForAll(std::vector<std::vector<bool>> gridLayout)
{
	for (int y = 0; y < this->gridY; y++)
	{
		for (int x = 0; x < this->gridX; x++)
		{
			this->SetStateAt(x, y, gridLayout[y][x]);
		}
	}
}


void Grid::RandomizeState()
{
	for (int x = 0; x < this->gridX; x++)
	{
		for (int y = 0; y < this->gridY; y++)
		{
			this->SetStateAt(x, y, rand() % 2);
		}
	}
}

int Grid::GetGridX()
{
	return this->gridX;
}

int Grid::GetGridY()
{
	return this->gridY;
}


void Grid::Draw(sf::RenderWindow & window)
{
	// draws grids
	int gridSize = this->gridX;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			window.draw(gridLines[i][j], 2, sf::Lines);
		}

		gridSize = this->gridY;
	}

	// draws cell fills
	sf::Vector2f rectSize(gridPixelSizeX, gridPixelSizeY);

	for (int x = 0; x < this->gridX; x++)
	{
		for (int y = 0; y < this->gridY; y++)
		{
			if (grid[x][y])
			{
				sf::RectangleShape cell(rectSize);
				cell.setPosition(x * gridPixelSizeX, y * gridPixelSizeY);

				window.draw(cell);
			}
		}
	}
}


void Grid::GenerateGridLines()
{
	gridLines = new sf::Vertex**[2];
	gridLines[0] = new sf::Vertex*[this->gridX];
	for (int j = 0; j < this->gridX; j++)
	{
		gridLines[0][j] = new sf::Vertex[2];
		for (int k = 0; k < 2; k++)
		{
			int second = (k == 0) ? 0 : windowSize;
			gridLines[0][j][k] = sf::Vertex(sf::Vector2f(j * this->gridPixelSizeX, second));
		}
	}

	gridLines[1] = new sf::Vertex*[this->gridY];
	for (int j = 0; j < this->gridY; j++)
	{
		gridLines[1][j] = new sf::Vertex[2];
		for (int k = 0; k < 2; k++)
		{
			int second = (k == 0) ? 0 : windowSize;
			gridLines[1][j][k] = sf::Vertex(sf::Vector2f(second, j * this->gridPixelSizeY));
		}
	}
}