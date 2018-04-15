//#include "Interpolate.hpp"

#include "LoadingClock.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#define EASE_SLOWEST .0075f
#define  EASE_SLOWER .01f
#define    EASE_SLOW .025f
#define     EASE_MED .05f
#define    EASE_FAST .075f
#define  EASE_FASTER .25f
#define EASE_FASTEST .50f

sf::Text statustext;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 720), "title");
	window.setVerticalSyncEnabled(true);

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	statustext.setFont(font);

	LoadingClock clock;
	clock.setPosition(sf::Vector2f(window.getSize().x - 25.0f, 25.0f));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Key::Space)
				{
					static bool loading = false;
					loading = !loading;
					clock.setLoading(!clock.loading);

					statustext.setString(std::to_string(loading));
				}
			}
		}

		clock.Update();

		window.clear();

		window.draw(clock);

		window.draw(statustext);

		window.display();
	}
}
