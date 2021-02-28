#include "Application.h"

#include <stdio.h>

#include "SFML/Graphics.hpp"

namespace Eagle
{
	void Run()
	{
		sf::RenderWindow window(sf::VideoMode(1280, 720), "Eagle2D");
		window.setFramerateLimit(60);

		sf::RectangleShape rect(sf::Vector2f(20.0f, 20.0f));
		rect.setFillColor(sf::Color(150, 50, 250));

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
			} 

			window.clear();
			window.draw(rect);
			window.display();
		}
	}
}