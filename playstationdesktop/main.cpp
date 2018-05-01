//#include "Interpolate.hpp"

#include "AnimationManager.hpp"
#include "Interpolate.hpp"
#include "LoadingClock.hpp"
#include "Background.hpp"

#include <SFML/Graphics.hpp>

#include <filesystem>
#include <iostream>
#include <string>

sf::Text statustext;

int mai3n()
{
	sf::RenderWindow window(sf::VideoMode(1080, 720), "title51");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	sf::RectangleShape test(sf::Vector2f(100, 100));
	AnimationManager anim;

	sf::Time t = sf::seconds(1);
	anim.addTask(test, sf::Vector2f(350, 350), EaseType::ElasticEaseOut, 1000);

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
					anim.clearTasks();
					anim.addTask(test, sf::Vector2f(0, 0), EaseType::ExpoEaseIn, 1000);
				}
			}
		}

		anim.Update();

		window.clear();
		window.draw(test);
		window.display();
	}

	return 0;
}

int mai2n()
{
	float t(0), b(0), c(0), d(0);

	float &time = t, &beginning = b, &change = c, &total = d;

	while (true)
	{
		std::cout << "time of tween: ";
		std::cin >> t;
		std::cout << "starting position: ";
		std::cin >> b;
		std::cout << "change in position: ";
		std::cin >> c;
		std::cout << "total duration: ";
		std::cin >> d;

		std::cout << "\n------------------------\n" << "position: " << c * (t / d) + b << "\n" << std::endl;

		std::cin.get();
	}

	return 0;
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 720), "title");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	statustext.setFont(font);

	LoadingClock clock;
	clock.setPosition(sf::Vector2f(window.getSize().x - 25.0f, 25.0f));

	Background background;
	background.setSize(sf::Vector2f(1080, 720));

	if (std::experimental::filesystem::exists("./psdk"))
	{
		std::experimental::filesystem::create_directory("./psdk");
	}

	sf::RectangleShape test;
	test.setSize(sf::Vector2f(100, 100));
	test.setFillColor(sf::Color::Blue);

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
		background.Update();

		window.clear();

		window.draw(background);
		window.draw(clock);
		window.draw(test);

		window.draw(statustext);

		window.display();
	}

	return 0;
}
