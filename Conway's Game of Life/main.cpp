#include <SFML/Graphics.hpp>
#include "Grid.h"

int main()
{
	const int windowSize = 1000;
	const int gridBoxSize = 25;

	sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Conway's Game of Life");

	Grid grid(windowSize, gridBoxSize);
	bool run = false;

	sf::Clock clock;
	double skippedTime = 0;

	while (window.isOpen())
	{
		const double elapsedTime = clock.restart().asMicroseconds() / 5000.;
		skippedTime += elapsedTime;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
				grid.ToggleGridCell(sf::Mouse::getPosition(window));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			run = true;
		}

		while (skippedTime > 10) {
			if (run)
			{
				grid.Update();
			}
			skippedTime -= 10;
		}

		window.clear(sf::Color::Black);

		grid.Draw(window);

		window.display();
	}

	return 0;
}
