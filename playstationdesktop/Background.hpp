#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "AnimationManager.hpp"
#include "Spline.hpp"

#include <SFML/Graphics.hpp>

#include <random>

class Background : public sf::Drawable
{
public:
	Background();
	~Background();

	void setSize(const sf::Vector2f& size);

	void HandleEvents(sf::Event& e);
	void Update();

	PhysicalAnimator anim;

	int maxDuration_ms = 10000;
	int minDuration_ms = 1000;

	// maximimum distance from top of screen
	int minHeight;
	// maximium distance from bottom of screen
	int maxHeight;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Spline spline;

	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	std::vector<sf::CircleShape*> circles;

	std::random_device dev;
	std::mt19937 rng;
	std::uniform_int_distribution<std::mt19937::result_type> dist;
};

#endif // !BACKGROUND_HPP
