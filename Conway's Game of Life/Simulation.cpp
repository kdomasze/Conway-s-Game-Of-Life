#include "Simulation.h"

Simulation::Simulation(Grid *gridObj)
{
	grid = gridObj;
}


Simulation::~Simulation()
{
}


void Simulation::Update()
{
	Grid* gridClone = grid->Clone();

	StepThroughGrid(gridClone);

	delete gridClone;
}


void Simulation::StepThroughGrid(Grid *gridClone)
{
	int size = gridClone->GetSize();

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			int cellsAlive = GetAliveCells(gridClone, x, y);

			UpdateCells(gridClone, x, y, cellsAlive);
		}
	}
}


int Simulation::GetAliveCells(Grid *gridClone, int x, int y)
{
	int size = gridClone->GetSize();

	int cellsAlive = 0;

	for (int xi = x - 1; xi <= x + 1; xi++)
	{
		for (int yi = y - 1; yi <= y + 1; yi++)
		{
			if (!(xi < 0 || yi < 0 || xi >= size || yi >= size))
			{
				if (gridClone->GetStateAt(xi, yi) && !(xi == x && yi == y))
				{
					cellsAlive++;
				}
			}
		}
	}

	return cellsAlive;
}


void Simulation::UpdateCells(Grid *gridClone, int x, int y, int cellsAlive)
{
	if (gridClone->GetStateAt(x, y))
	{
		if (cellsAlive < 2 || cellsAlive > 3)
		{
			grid->SetStateAt(x, y, false);
		}
	}
	else
	{
		if (cellsAlive == 3)
		{
			grid->SetStateAt(x, y, true);
		}
	}
}