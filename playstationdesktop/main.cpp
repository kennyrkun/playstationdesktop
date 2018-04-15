//#include "Interpolate.hpp"

#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <thread>
#include <string>
#include <ctime>

#define EASE_SLOWEST .0075f
#define  EASE_SLOWER .01f
#define    EASE_SLOW .025f
#define     EASE_MED .05f
#define    EASE_FAST .075f
#define  EASE_FASTER .25f
#define EASE_FASTEST .50f

#define ANIM_ROTATE 1

// 6 degrees per minutest
// 30 degrees per hourst

int spinTo(sf::Shape &shape, float rotation, float ease)
{
	if (static_cast<int>(shape.getRotation()) == static_cast<int>(rotation))
		return 1;

	float xx = (rotation - shape.getRotation()) * ease;
	shape.rotate(xx);
}

class ARotation
{
public:
	ARotation(sf::RectangleShape &shape, float &target, float ease, bool constant) : shape(shape), targetRotation(target), ease(ease), constant(constant)
	{
		std::cout << "arot" << std::endl;
	}

	~ARotation()
	{
		std::cout << "darot" << std::endl;
	}

	float originalRotation;
	float currentRotation;
	float &targetRotation;

	float ease;

	bool isDoing = true;
	bool constant;

	sf::RectangleShape& shape;

	void Update()
	{
//		shape.rotate(10.f * interpolate::linear(duration.asSeconds(), 0.f, 1.f, 1.f), 0.f);
		currentRotation = shape.getRotation();

		if (spinTo(shape, targetRotation, ease) == 1)
			isDoing = false;
	}
};

class AnimationManager
{
public:
	AnimationManager()
	{
		std::cout << "aman" << std::endl;
	}

	~AnimationManager()
	{
		for (size_t i = 0; i < tasks.size(); i++)
			delete tasks[i];
		tasks.clear();

		std::cout << "daman" << std::endl;
	}

	void addTask(sf::RectangleShape& shape, float &rotation, float ease, bool constant = false)
	{
		ARotation* task = new ARotation(shape, rotation, ease, constant);

		tasks.push_back(task);
	}

	void clearTasks()
	{
		for (size_t i = 0; i < tasks.size(); i++)
			delete tasks[i];
		tasks.clear();
	}

	void Update()
	{
//		timeSinceLastUpdate += tickClock.restart();
//		if (timeSinceLastUpdate > TimePerFrame)
//		{
//			timeSinceLastUpdate -= TimePerFrame;
//			duration += TimePerFrame;

			for (size_t i = 0; i < tasks.size(); i++)
			{
				tasks[i]->Update();

				if (!tasks[i]->constant && !tasks[i]->isDoing)
				{
					delete tasks[i];
					tasks.erase(std::remove(tasks.begin(), tasks.end(), tasks[i]), tasks.end());
				}
			}
//		}
	}

//	sf::Clock tickClock;
//	sf::Time timeSinceLastUpdate = sf::Time::Zero;
//	sf::Time duration = sf::Time::Zero;
//	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	std::vector<ARotation*> tasks;
};

sf::Text hourst, minutest, secondst;

class LoadingClock : public sf::Drawable
{
public:
	LoadingClock(float radius = 50)
	{
		outer.setRadius(radius);
		outer.setFillColor(sf::Color::Transparent);
		outer.setOutlineColor(sf::Color::White);
		outer.setOutlineThickness(-2);
		outer.setOrigin(sf::Vector2f(outer.getLocalBounds().width / 2, outer.getLocalBounds().height / 2));
		outer.setPosition(0, 0);
		outer.setPointCount(100);

		inner.setRadius(outer.getRadius() / 12);
		inner.setOrigin(sf::Vector2f(inner.getLocalBounds().width / 2, inner.getLocalBounds().height / 2));
		inner.setPosition(outer.getPosition());

		loadingHand.setSize(sf::Vector2f(2.0f, -outer.getRadius()));
		loadingHand.setOrigin(sf::Vector2f(loadingHand.getLocalBounds().width / 2, 0));
		loadingHand.setPosition(inner.getPosition());

		minuteHand.setSize(sf::Vector2f(1.5f, -outer.getRadius()));
		minuteHand.setOrigin(sf::Vector2f(minuteHand.getLocalBounds().width / 2, 0));
		minuteHand.setPosition(inner.getPosition());

		hourHand.setSize(sf::Vector2f(2.0f, -(outer.getRadius() - 5)));
		hourHand.setOrigin(sf::Vector2f(hourHand.getLocalBounds().width / 2, 0));
		hourHand.setPosition(inner.getPosition());

		secondHand.setSize(sf::Vector2f(1.0f, -outer.getRadius()));
		secondHand.setOrigin(sf::Vector2f(secondHand.getLocalBounds().width / 2, 0));
		secondHand.setPosition(inner.getPosition());
		secondHand.setFillColor(sf::Color::Red);

		outie.setFillColor(sf::Color(200, 200, 200));
		outie.setOrigin(outie.getLocalBounds().width / 2, outie.getLocalBounds().height / 2);
		outie.setPosition(inner.getPosition());

		anim.addTask(hourHand, hourHandAngle, EASE_MED, true);
		anim.addTask(minuteHand, minuteHandAngle, EASE_MED, true);
		anim.addTask(secondHand, secondHandAngle, EASE_MED, true);
	}

	~LoadingClock()
	{
		anim.clearTasks();
	}

	void Update()
	{
		if (switchingstates)
		{
			if (switchingtoloading)
			{
				if (static_cast<int>(hourHand.getRotation()) == zero - 1)
				{
					if (static_cast<int>(minuteHand.getRotation()) == zero - 1)
					{
						if (static_cast<int>(secondHand.getRotation()) == zero - 1)
						{
							readytoswitch = true;
							switchingstates = false;

							loading = true;
							switchingtoloading = false;

							std::cout << "Ready to switch to loading" << std::endl;
						}
					}
				}
			}
			else if (switchingtoclock)
			{
				if (loadingHand.getRotation() == 0)
				{
					readytoswitch = true;
					switchingstates = false;

					minuteHand.setRotation(loadingHand.getRotation());
					hourHand.setRotation(loadingHand.getRotation());
					secondHand.setRotation(loadingHand.getRotation());

					anim.clearTasks();
					anim.addTask(hourHand, hourHandAngle, EASE_MED, true);
					anim.addTask(minuteHand, minuteHandAngle, EASE_MED, true);
					anim.addTask(secondHand, secondHandAngle, EASE_MED, true);

					loading = false;
					switchingtoclock = false;

					std::cout << "Ready to switch to clock" << std::endl;
				}
			}
		}

		if (loading)
		{
			loadingHand.rotate(loadingSpinSpeed);

			// TODO: make this look right
			int a = outie.getFillColor().a;
			int outdist = outer.getRadius();

			if (outie.getRadius() < outdist)
			{
				outie.setFillColor(sf::Color(200, 200, 200, a - (255 / outdist)));

				outie.setRadius(outie.getRadius() + 1);
				outie.setOrigin(outie.getLocalBounds().width / 2, outie.getLocalBounds().height / 2);
			}
			else
			{
				if (loadingHand.getRotation() == 0)
				{
					std::cout << "resetting" << std::endl;

					outie.setRadius(0);
					outie.setFillColor(sf::Color(200, 200, 200, (a = 255)));
				}
			}
		}
		else // clock
		{
			SYSTEMTIME systime;
			GetLocalTime(&systime);
			second = systime.wSecond;
			minute = systime.wMinute + second / 60;

			hour = systime.wHour;

			if (hour > 12)
				hour -= 12;

			hour += minute / 60;

			hourHandAngle = hour * 30;
			minuteHandAngle = minute * 6;
			secondHandAngle = second * 6;

			// TODO: fix this
			if (secondHandAngle == 0)
				secondHand.setRotation(0);

			if (minuteHandAngle == 0)
				minuteHand.setRotation(0);

			if (hourHandAngle == 0)
				hourHand.setRotation(0);
		}

		anim.Update();

		hourst.setString(std::to_string(hourHand.getRotation()));
		minutest.setString(std::to_string(minuteHand.getRotation()));
		secondst.setString(std::to_string(secondHand.getRotation()));
	}

	void setLoading(bool loading)
	{
		switchingstates = true;

		if (loading)
		{
			std::cout << "switching to loading state" << std::endl;

			switchingtoloading = true;

			anim.clearTasks();

			anim.addTask(hourHand, zero, EASE_FAST);
			anim.addTask(minuteHand, zero, EASE_FAST);
			anim.addTask(secondHand, zero, EASE_FAST);

			loadingHand.setRotation(zero);
		}
		else
		{
			std::cout << "switching to clock state" << std::endl;

			switchingtoclock = true;

//			anim.clearTasks();

//			anim.addTask(hourHand, hourHandAngle);
//			anim.addTask(minuteHand, minuteHandAngle);
//			anim.addTask(secondHand, secondHandAngle);
		}
	}

	void setPosition(const sf::Vector2f& pos)
	{
		outer.setPosition(pos);
		inner.setPosition(outer.getPosition());

		outie.setPosition(inner.getPosition());

		loadingHand.setPosition(inner.getPosition());
		minuteHand.setPosition(inner.getPosition());
		hourHand.setPosition(inner.getPosition());
		secondHand.setPosition(inner.getPosition());
	}

	sf::Vector2f getPosition()
	{
		return inner.getPosition();
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (!loading)
		{
			target.draw(minuteHand);
			target.draw(hourHand);
			target.draw(secondHand);
		}
		else
		{
			target.draw(outie);
			target.draw(loadingHand);
		}

		target.draw(inner);
		target.draw(outer);
	}

	AnimationManager anim;

	sf::CircleShape outer;
	sf::CircleShape inner;
	sf::CircleShape outie;

	sf::RectangleShape loadingHand;
	sf::RectangleShape minuteHand;
	sf::RectangleShape hourHand;
	sf::RectangleShape secondHand;

	float hour;
	float minute;
	float second;

	float hourHandAngle;
	float minuteHandAngle;
	float secondHandAngle;

	float loadingSpinSpeed = 5;

	bool loading = false;

private:
	bool switchingstates;
	bool switchingtoloading;
	bool switchingtoclock;
	bool readytoswitch;

	float zero = 360;
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 720), "title");
	window.setVerticalSyncEnabled(true);

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	hourst.setFont(font);
	minutest.setFont(font);
	secondst.setFont(font);

	minutest.setPosition(0, 30);
	secondst.setPosition(0, 60);

	LoadingClock clock;
	clock.setPosition(sf::Vector2f(window.getSize().x - 55, 55));

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
					clock.setLoading(!clock.loading);
				}
			}
		}

		clock.Update();

		window.clear();

		window.draw(clock);

		window.draw(hourst);
		window.draw(minutest);
		window.draw(secondst);

		window.display();
	}
}
