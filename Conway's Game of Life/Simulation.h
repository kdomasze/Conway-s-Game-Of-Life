#pragma once
#include "Grid.h"

class Simulation
{
	public:
		Simulation(Grid *gridObj);
		~Simulation();
		
		void Update();

	private:
		Grid *grid;

		void StepThroughGrid(Grid * gridClone);
		int GetAliveCells(Grid * gridClone, int x, int y);
		void UpdateCells(Grid * gridClone, int x, int y, int cellsAlive);
};
