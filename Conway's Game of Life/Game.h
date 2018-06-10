#pragma once
#include "ApplicationAdapter.h"
#include "Grid.h"
#include "Simulation.h"
#include "Config.h"

class Game : public ApplicationAdapter
{
	public:
		Game(sf::RenderWindow *window);
		~Game() {}

		void Create(Config *config) override;
		void PollEvent(sf::Event event) override;
		void Update() override;
		void Render() override;
		void Dispose() override;
	private: 
		sf::View view;

		Config *config;
		Grid *grid;
		Simulation *sim;

		bool run;

		void KeepViewportBounded();
};

