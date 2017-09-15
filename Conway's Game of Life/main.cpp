#include <SFML/Graphics.hpp>
#include "GridLines.h"

int main()
{
	const int windowSize = 800;
	const int gridBoxSize = 16;

	sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Conway's Game of Life");

	GridLines gridLines(windowSize, gridBoxSize);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		gridLines.Draw(window);

		window.display();
	}

	return 0;
}
