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
	for (int x = 0; x < gridClone->GetGridX(); x++)
	{
		for (int y = 0; y < gridClone->GetGridY(); y++)
		{
			int cellsAlive = GetAliveCells(gridClone, x, y);

			UpdateCells(gridClone, x, y, cellsAlive);
		}
	}
}


int Simulation::GetAliveCells(Grid *gridClone, int x, int y)
{
	int cellsAlive = 0;

	for (int x_internal = x - 1; x_internal <= x + 1; x_internal++)
	{
		for (int y_internal = y - 1; y_internal <= y + 1; y_internal++)
		{
			int x_internalFixed = x_internal;
			int y_internalFixed = y_internal;

			if (x_internalFixed < 0) x_internalFixed = gridClone->GetGridX() - 1;
			if (y_internalFixed < 0) y_internalFixed = gridClone->GetGridY() - 1;

			if (x_internalFixed >= gridClone->GetGridX()) x_internalFixed = 0;
			if (y_internalFixed >= gridClone->GetGridY()) y_internalFixed = 0;

			if (gridClone->GetStateAt(x_internalFixed, y_internalFixed) && !(x_internalFixed == x && y_internalFixed == y))
			{
				cellsAlive++;
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