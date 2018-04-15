#include "LoadingClock.hpp"

#include <Windows.h>

LoadingClock::LoadingClock(float radius)
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

LoadingClock::~LoadingClock()
{
	anim.clearTasks();
}

void LoadingClock::Update()
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
		float a = outie.getFillColor().a;
		float outdist = outer.getRadius();

		if (outie.getRadius() < outdist - 1.25)
		{
			outie.setFillColor(sf::Color(200, 200, 200, a - 4));

			outie.setRadius(outie.getRadius() + 0.3f);
			outie.setOrigin(outie.getLocalBounds().width / 2, outie.getLocalBounds().height / 2);
		}
		else
		{
			if (loadingHand.getRotation() == 0)
			{
				std::cout << "resetting at " << outie.getRadius() << ", " << std::to_string(outie.getFillColor().a) << std::endl;

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
}

void LoadingClock::setLoading(bool loading)
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

void LoadingClock::setPosition(const sf::Vector2f& pos)
{
	outer.setPosition(pos);
	inner.setPosition(outer.getPosition());

	outie.setPosition(inner.getPosition());

	loadingHand.setPosition(inner.getPosition());
	minuteHand.setPosition(inner.getPosition());
	hourHand.setPosition(inner.getPosition());
	secondHand.setPosition(inner.getPosition());
}

sf::Vector2f LoadingClock::getPosition()
{
	return inner.getPosition();
}

void LoadingClock::draw(sf::RenderTarget& target, sf::RenderStates states) const
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
