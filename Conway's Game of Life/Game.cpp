#include "Game.h"
#include <SFML/Graphics.hpp>

Game::Game(sf::RenderWindow *window) : ApplicationAdapter(window)
{

}

void Game::Create(Config *config)
{
	// prepare viewport
	view.setCenter(window->getSize().x / 2.0f, window->getSize().x / 2.0f);
	view.setSize(1000, 1000);
	view.setViewport(sf::FloatRect(0, 0, 1, 1));

	window->setView(view);

	this->config = config;

	// prepare grid
	grid = new Grid(config->GetgridsX(), config->GetgridsY(), window->getSize().x);

	// load grid data from config
	grid->SetStateForAll(config->getGridLayout());

	// start simulation
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
			switch(event.mouseButton.button)
			{
				case sf::Mouse::Left:
					// map pixel coords to grid coords to find which cell is interacted with, and toggle its state
					sf::Vector2f worldPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

					float x = worldPos.x;
					float y = worldPos.y;

					int gridXPos = (int)floor(x / (window->getSize().x / config->GetgridsX()));
					int gridYPos = (int)floor(y / (window->getSize().y / config->GetgridsY()));

					grid->SetStateAt(gridXPos, gridYPos, !grid->GetStateAt(gridXPos, gridYPos));
					break;
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
				case sf::Keyboard::R:
					grid->RandomizeState();
					break;
				case sf::Keyboard::Up:
					view.move(0, -100);
					break;
				case sf::Keyboard::Down:
					view.move(0, 100);
					break;
				case sf::Keyboard::Left:
					view.move(-100, 0);
					break;
				case sf::Keyboard::Right:
					view.move(100, 0);
					break;
			}
			break;
		case sf::Event::MouseWheelScrolled:
			switch(event.mouseWheelScroll.wheel)
			{
				case sf::Mouse::VerticalWheel:
					if(event.mouseWheelScroll.delta > 0)
					{
						view.zoom(0.9f);
					}
					else if(event.mouseWheelScroll.delta < 0)
					{
						view.zoom(1.1f);
					}
					break;
			}
			break;
	}
}


void Game::Update()
{
	KeepViewportBounded();

	if (run)
	{
		sim->Update();
	}
}


void Game::Render()
{
	window->setView(view);
	grid->Draw(*window);
}


void Game::Dispose()
{
	delete grid;
	delete sim;
}

void Game::KeepViewportBounded()
{
	// TODO: there seems to be an issue with this function. Window doens't resize properly.
	if (view.getSize().x > window->getSize().x || view.getSize().y > window->getSize().y)
	{
		view.setSize((float)window->getSize().x, (float)window->getSize().y);
	}

	if (view.getCenter().x + (view.getSize().x / 2.0f) > window->getSize().x)
	{
		view.setCenter(window->getSize().x - (view.getSize().x / 2.0f), view.getCenter().y);
	}

	if (view.getCenter().x - (view.getSize().x / 2.0f) < 0)
	{
		view.setCenter((view.getSize().x / 2.0f), view.getCenter().y);
	}

	if (view.getCenter().y + (view.getSize().y / 2.0f) > window->getSize().y)
	{
		view.setCenter(view.getCenter().x, window->getSize().y - (view.getSize().y / 2.0f));
	}

	if (view.getCenter().y - (view.getSize().y / 2.0f) < 0)
	{
		view.setCenter(view.getCenter().x, view.getSize().y / 2.0f);
	}
}