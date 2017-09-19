#include <SFML/Graphics.hpp>
#include "ApplicationAdapter.h"
#include "Game.h"

int main()
{
	const int windowWidth = 1000;
	const int windowHeight = 1000;

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Conway's Game of Life");

	ApplicationAdapter *game = new Game(&window);
	
	game->Create();

	sf::Clock clock;
	double skippedTime = 0;

	while (window.isOpen())
	{
		const double elapsedTime = clock.restart().asMicroseconds() / 1000.;
		skippedTime += elapsedTime;

		while (skippedTime > 10)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				game->PollEvent(event);
			}

			game->Update();

			skippedTime -= 10;
		}

		window.clear(sf::Color::Black);
		game->Render();
		window.display();
	}

	game->Dispose();
	delete game;
	return 0;
}