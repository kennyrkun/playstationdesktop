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

	inner.setRadius(outer.getRadius() / 8);
	inner.setOrigin(sf::Vector2f(inner.getLocalBounds().width / 2, inner.getLocalBounds().height / 2));
	inner.setPosition(outer.getPosition());

	loadingHand.setSize(sf::Vector2f(2.0f, -outer.getRadius()));
	loadingHand.setOrigin(sf::Vector2f(loadingHand.getLocalBounds().width / 2, 0));
	loadingHand.setPosition(inner.getPosition());

	minuteHand.setSize(sf::Vector2f(2.f, -outer.getRadius()));
	minuteHand.setOrigin(sf::Vector2f(minuteHand.getLocalBounds().width / 2, 0));
	minuteHand.setPosition(inner.getPosition());

	hourHand.setSize(sf::Vector2f(2.f, -(outer.getRadius() - 5)));
	hourHand.setOrigin(sf::Vector2f(hourHand.getLocalBounds().width / 2, 0));
	hourHand.setPosition(inner.getPosition());

	secondHand.setSize(sf::Vector2f(2.0f, -outer.getRadius()));
	secondHand.setOrigin(sf::Vector2f(secondHand.getLocalBounds().width / 2, 0));
	secondHand.setPosition(inner.getPosition());
	secondHand.setFillColor(sf::Color::Red);

	outie.setFillColor(sf::Color(200, 200, 200));
	outie.setOrigin(outie.getLocalBounds().width / 2, outie.getLocalBounds().height / 2);
	outie.setPosition(inner.getPosition());
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
			if (static_cast<int>(hourHand.getRotation()) == zero)
			{
				if (static_cast<int>(minuteHand.getRotation()) == zero)
				{
					if (static_cast<int>(secondHand.getRotation()) == zero)
					{
						readytoswitch = true;
						switchingstates = false;

						loading = true;
						clock = false;
						switchingtoloading = false;

						std::cout << "Ready to switch to loading" << std::endl;
					}
				}
			}

			if (anim.tasks.empty())
			{
				readytoswitch = true;
				switchingstates = false;

				loading = true;
				clock = false;
				switchingtoloading = false;

				std::cout << "Ready to switch to loading" << std::endl;
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
				anim.addRotationTask(hourHand, hourHandAngle, EaseType::LinearEaseNone, 500, true);
				anim.addRotationTask(minuteHand, minuteHandAngle, EaseType::LinearEaseNone, 500, true);
				anim.addRotationTask(secondHand, secondHandAngle, EaseType::LinearEaseNone, 500, true);

				clock = true;
				loading = false;
				switchingtoclock = false;

				std::cout << "switched to clock" << std::endl;
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
			// TODO: find a better colour for this, as the grey is not visible ont the background,
			// but the black looks to bad on the grey background
			outie.setFillColor(sf::Color(0, 0, 0, a - 4));

			outie.setRadius(outie.getRadius() + 0.3f);
			outie.setOrigin(outie.getLocalBounds().width / 2, outie.getLocalBounds().height / 2);
		}
		else
		{
			if (loadingHand.getRotation() == 0)
			{
				outie.setRadius(0);
				outie.setFillColor(sf::Color(0, 0, 0, (a = 255)));
			}
		}
	}
	else if (clock) // clock
	{
		if (anim.tasks.empty())
		{
			updateTime();

			hourHandAngle = hour * 30;
			minuteHandAngle = minute * 6;
			secondHandAngle = second * 6;

			hourHand.setRotation(hourHandAngle);
			minuteHand.setRotation(minuteHandAngle);
			secondHand.setRotation(secondHandAngle);
		}
	}
	else
	{
		std::cout << "something is wrong" << std::endl;
	}

	anim.Update();
}

void LoadingClock::setLoading(bool loading)
{
	switchingstates = true;

	if (loading)
	{
		std::cout << "switching to loading state" << std::endl;

		switchingtoclock = false;
		switchingtoloading = true;

		anim.clearTasks();
		anim.addRotationTask(hourHand, zero, EaseType::CubicEaseIn, 1000);
		anim.addRotationTask(minuteHand, zero, EaseType::CubicEaseIn, 1000);
		anim.addRotationTask(secondHand, zero, EaseType::CubicEaseIn, 1000);

		loadingHand.setRotation(zero);
	}
	else
	{
		std::cout << "switching to clock state" << std::endl;

		switchingtoloading = false;
		switchingtoclock = true;

		updateTime();
		hourHandAngle = hour * 30;
		minuteHandAngle = minute * 6;
		secondHandAngle = second * 6;

		anim.clearTasks();
		anim.addRotationTask(hourHand, hourHandAngle, EaseType::ExpoEaseOut, 500, true);
		anim.addRotationTask(minuteHand, minuteHandAngle, EaseType::ExpoEaseOut, 500, true);
		anim.addRotationTask(secondHand, secondHandAngle, EaseType::ExpoEaseOut, 500, true);
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
	if (clock)
	{
		target.draw(secondHand);
		target.draw(minuteHand);
		target.draw(hourHand);
	}
	else if (loading)
	{
		target.draw(outie);
		target.draw(loadingHand);
	}

	target.draw(inner);
	target.draw(outer);
}

// Private:

void LoadingClock::updateTime()
{
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	second = systime.wSecond;
	minute = systime.wMinute + second / 60;
	hour = systime.wHour + minute / 60;

	// normal clocks cannot show 24 hour time
	// if we're in 24 hour format, subtract 12
	if (hour > 12)
		hour -= 12;
}
