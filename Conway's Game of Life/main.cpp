#include <SFML/Graphics.hpp>
#include "ApplicationAdapter.h"
#include "Game.h"
#include "Config.h"

#include <string>
#include <iostream>

#include "vld.h"

int main(int argc, const char * argv[])
{

	const int windowWidth = 1000;
	const int windowHeight = 1000;

	// get file name if saved data is opened
	std::string configFileName = "null";
	if (argc > 1)
	{
		configFileName = argv[1];
	}

	Config config(configFileName);

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Conway's Game of Life");

	Game game(&window);
	
	game.Create(&config);

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
				game.PollEvent(event);
			}

			game.Update();

			skippedTime -= 10;
		}

		window.clear(sf::Color::Black);
		game.Render();
		window.display();
	}

	game.Dispose();
	return 0;
}