#include <SFML\Graphics.hpp>

#include <iostream>
#include <thread>
#include <string>

int mai2n();

void main()
{
	{
		bool right(false);

		do
		{
			std::cout << "view (T)est or (A)traxian" << std::endl;
			std::string line;
			std::getline(std::cin, line);

			if (line == "a")
			{
				mai2n();
			}
			else if (line == "t")
			{
				right = true;
			}
			else
			{
				std::cout << "wrong" << std::endl;
			}
		} while (!right);
	}

	sf::RenderWindow window(sf::VideoMode(800, 600), "title");
	window.setVerticalSyncEnabled(true);

	sf::CircleShape outer;
	sf::CircleShape inner;
	sf::CircleShape outie;
	sf::RectangleShape spinner;

	outer.setRadius(30);
	outer.setFillColor(sf::Color::Transparent);
	outer.setOutlineColor(sf::Color::White);
	outer.setOutlineThickness(-4);
	outer.setOrigin(sf::Vector2f(outer.getLocalBounds().width / 2, outer.getLocalBounds().height / 2));
	outer.setPosition(window.getView().getCenter());

	inner.setRadius(5);
	inner.setOrigin(sf::Vector2f(inner.getLocalBounds().width / 2, inner.getLocalBounds().height / 2));
	inner.setPosition(outer.getPosition());

	spinner.setSize(sf::Vector2f(4, 30));
	spinner.setOrigin(sf::Vector2f(spinner.getLocalBounds().width / 2, 0));
	spinner.setPosition(inner.getPosition());

	outie.setFillColor(sf::Color(200, 200, 200));
	outie.setOrigin(outie.getLocalBounds().width / 2, outie.getLocalBounds().height / 2);
	outie.setPosition(inner.getPosition());

	int spinspeed = 5;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::EventType::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Key::Num0)
					spinspeed = 0;
				else if (event.key.code == sf::Keyboard::Key::Num1)
					spinspeed = 1;
				else if (event.key.code == sf::Keyboard::Key::Num2)
					spinspeed = 2;
				else if (event.key.code == sf::Keyboard::Key::Num3)
					spinspeed = 3;
				else if (event.key.code == sf::Keyboard::Key::Num4)
					spinspeed = 4;
				else if (event.key.code == sf::Keyboard::Key::Num5)
					spinspeed = 5;
				else if (event.key.code == sf::Keyboard::Key::Num6)
					spinspeed = 6;
				else if (event.key.code == sf::Keyboard::Key::Num7)
					spinspeed = 7;
				else if (event.key.code == sf::Keyboard::Key::Num8)
					spinspeed = 8;
				else if (event.key.code == sf::Keyboard::Key::Num9)
					spinspeed = 9;
			}
		}

		spinner.rotate(spinspeed);

		int a = outie.getFillColor().a;
		int outdist = 50;

		if (outie.getRadius() < outdist)
		{
			//			if (outie.getRadius() > outer.getRadius())
			{
				outie.setFillColor(sf::Color(200, 200, 200, a - 5));
			}

			outie.setRadius(outie.getRadius() + 1);
			outie.setOrigin(outie.getLocalBounds().width / 2, outie.getLocalBounds().height / 2);
		}
		else
		{
			outie.setRadius(0);
			outie.setFillColor(sf::Color(200, 200, 200, (a = 255)));
		}

		window.clear();

		window.draw(outie);
		window.draw(spinner);
		window.draw(outer);
		window.draw(inner);

		window.display();
	}
}