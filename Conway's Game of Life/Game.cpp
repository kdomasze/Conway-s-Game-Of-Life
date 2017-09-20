#include "Game.h"
#include <SFML/Graphics.hpp>

Game::Game(sf::RenderWindow *window) : ApplicationAdapter(window)
{

}

void Game::Create()
{
	view.setCenter(window->getSize().x / 2, window->getSize().x / 2);
	view.setSize(1000, 1000);
	view.setViewport(sf::FloatRect(0, 0, 1, 1));

	window->setView(view);

	gridCount = 100;

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
			switch(event.mouseButton.button)
			{
				case sf::Mouse::Left:
					sf::Vector2f worldPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

					float x = worldPos.x;
					float y = worldPos.y;

					int gridXPos = floor(x / (window->getSize().x / gridCount));
					int gridYPos = floor(y / (window->getSize().x / gridCount));

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
						view.zoom(0.9);
					}
					else if(event.mouseWheelScroll.delta < 0)
					{
						view.zoom(1.1);
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
	if (view.getSize().x > window->getSize().x || view.getSize().y > window->getSize().y)
	{
		view.setSize(window->getSize().x, window->getSize().y);
	}

	if (view.getCenter().x + (view.getSize().x / 2.) > window->getSize().x)
	{
		view.setCenter(window->getSize().x - (view.getSize().x / 2.), view.getCenter().y);
	}

	if (view.getCenter().x - (view.getSize().x / 2.) < 0)
	{
		view.setCenter((view.getSize().x / 2.), view.getCenter().y);
	}

	if (view.getCenter().y + (view.getSize().y / 2.) > window->getSize().y)
	{
		view.setCenter(view.getCenter().x, window->getSize().y - (view.getSize().y / 2.));
	}

	if (view.getCenter().y - (view.getSize().y / 2.) < 0)
	{
		view.setCenter(view.getCenter().x, view.getSize().y / 2.);
	}
}