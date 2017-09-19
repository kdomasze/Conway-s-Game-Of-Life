#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Simulation.h"

int main()
{
	const int windowSize = 1000;
	const int gridCount = 50;

	sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Conway's Game of Life");

	Grid *grid = new Grid(gridCount, windowSize);
	Simulation sim(grid);
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
			{
				float x = sf::Mouse::getPosition(window).x;
				float y = sf::Mouse::getPosition(window).y;

				int gridXPos = floor(x / (windowSize / gridCount));
				int gridYPos = floor(y / (windowSize / gridCount));

				grid->SetStateAt(gridXPos, gridYPos, !grid->GetStateAt(gridXPos,gridYPos));
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			run = true;
		}

		while (skippedTime > 10) {
			if (run)
			{
				sim.Update();
			}
			skippedTime -= 10;
		}

		window.clear(sf::Color::Black);

		grid->Draw(window);

		window.display();
	}

	delete grid;
	return 0;
}
