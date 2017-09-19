#include "Game.h"
#include <SFML/Graphics.hpp>

Game::Game(sf::RenderWindow *window) : ApplicationAdapter(window)
{

}

void Game::Create()
{
	gridCount = 50;

	grid = new Grid(gridCount, window->getSize().x);
	sim = new Simulation(grid);

	run = false;
}

void Game::PollEvent(sf::Event event)
{
	switch(event.type)
	{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::MouseButtonReleased:
			if(event.mouseButton.button == sf::Mouse::Left)
			{
				float x = sf::Mouse::getPosition(*window).x;
				float y = sf::Mouse::getPosition(*window).y;

				int gridXPos = floor(x / (window->getSize().x / gridCount));
				int gridYPos = floor(y / (window->getSize().x / gridCount));

				grid->SetStateAt(gridXPos, gridYPos, !grid->GetStateAt(gridXPos, gridYPos));
			}
			break;
		case sf::Event::KeyPressed:
			switch(event.key.code)
			{
				case sf::Keyboard::Return:
					run = true;
					break;
				case sf::Keyboard::Escape:
					run = false;
					break;
			}
			break;
	}
}


void Game::Update()
{
	if (run)
	{
		sim->Update();
	}
}


void Game::Render()
{
	grid->Draw(*window);
}


void Game::Dispose()
{
	delete grid;
	delete sim;
}