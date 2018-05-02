#include "PlaystationDesktop.hpp"

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <string>

PlaystationDesktop::PlaystationDesktop()
{
}

PlaystationDesktop::~PlaystationDesktop()
{
}

void PlaystationDesktop::start()
{
	window.create(sf::VideoMode(1080, 720), "title");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

	statustext.setFont(font);

	clock.setPosition(sf::Vector2f(window.getSize().x - 25.0f, 25.0f));

	background.setSize(sf::Vector2f(1080, 720));

	if (std::experimental::filesystem::exists("./psdk"))
		std::experimental::filesystem::create_directory("./psdk");

	isRunning = true;
}

void PlaystationDesktop::shutdown()
{
}

void PlaystationDesktop::HandleEvents()
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
}

void PlaystationDesktop::Update()
{
	clock.Update();
	background.Update();
}

void PlaystationDesktop::Draw()
{
	window.clear();

	window.draw(background);
	window.draw(clock);

	window.draw(statustext);

	window.display();
}
