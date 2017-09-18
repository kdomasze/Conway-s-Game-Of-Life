#include <SFML/Graphics.hpp>
#include "Grid.h"

int main()
{
	const int windowSize = 1000;
	const int gridBoxSize = 100;

	sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Conway's Game of Life");
	window.setKeyRepeatEnabled(false);

	Grid grid(windowSize, gridBoxSize);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
				grid.ToggleGridCell(sf::Mouse::getPosition(window));
		}

		window.clear(sf::Color::Black);

		grid.Draw(window);

		window.display();
	}

	return 0;
}
