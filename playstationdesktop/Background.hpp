#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>

#include "Spline.hpp"

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
};

#endif // !BACKGROUND_HPP
