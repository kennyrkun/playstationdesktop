#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "AnimationManager.hpp"
#include "Spline.hpp"

#include <SFML/Graphics.hpp>

class Background : public sf::Drawable
{
public:
	Background();
	~Background();

	void setSize(const sf::Vector2f& size);

	void HandleEvents(sf::Event& e);
	void Update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<sf::CircleShape*> circles;

	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	sf::Spline spline;

	AnimationManager anim;
};

#endif // !BACKGROUND_HPP
