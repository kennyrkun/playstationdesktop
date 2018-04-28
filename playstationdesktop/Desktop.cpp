#include "Desktop.hpp"

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <string>

Desktop::Desktop()
{
}

Desktop::~Desktop()
{
}

void Desktop::start()
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
}

void Desktop::shutdown()
{
}

void Desktop::HandleEvents()
{
}

void Desktop::Update()
{
}

void Desktop::Draw()
{
}
