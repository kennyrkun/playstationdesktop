#ifndef LOADING_CLOCK_HPP
#define LOADING_CLOCK_HPP

#include <SFML\Graphics.hpp>
#include "AnimationManager.hpp"

class LoadingClock : public sf::Drawable
{
public:
	LoadingClock(float radius = 20);
	~LoadingClock();

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
	bool clock = true;

	void setLoading(bool loading);

	// relative to the center
	void setPosition(const sf::Vector2f& pos);
	sf::Vector2f getPosition();

	void Update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	bool switchingstates;
	bool switchingtoloading;
	bool switchingtoclock;
	bool readytoswitch;

	float zero = 360;
};

#endif // !LOADING_CLOCK_HPP
