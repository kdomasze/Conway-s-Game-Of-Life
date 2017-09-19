#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class ApplicationAdapter
{
	public:
		ApplicationAdapter(sf::RenderWindow *window);
		virtual ~ApplicationAdapter() {}

		virtual void Create() = 0;
		virtual void PollEvent(sf::Event event) = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Dispose() = 0;
	
	protected:
		sf::RenderWindow *window;
};

