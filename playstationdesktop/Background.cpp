#include "Background.hpp"

Background::Background()
{
	background.setTexture(&backgroundTexture);

	std::vector<sf::Vector2f> vertices = { { 50.f, 50.f }, { 100.f, 100.f }, { 150.f, 150.f }, { 200.f, 200.f }, { 250.f, 250.f }, { 300.f, 300.f }, { 350.f, 350.f } };
	spline.addVertices(0, vertices);
	spline.setBezierInterpolation(); // enable Bezier spline
	spline.setInterpolationSteps(20); // curvature resolution

	for (size_t i = 0; i < spline.getVertexCount(); i++)
	{
		sf::CircleShape* cir = new sf::CircleShape(5);
		circles.push_back(cir);
	}
}

Background::~Background()
{
}

void Background::setSize(const sf::Vector2f& size)
{
	background.setSize(size);
}

void Background::HandleEvents(sf::Event& e)
{
}

void Background::Update()
{
	for (size_t i = 0; i < spline.getVertexCount(); i++)
	{
		if (spline[i].position.y == 500)
		{
			// animation new position 220
		}

		if (spline[i].position.y == 220)
		{
			// animation new position 500
		}

		circles[i]->setPosition(spline[i].position);
	}

	spline.smoothHandles(); // automatically position handles to create a smooth curve that passes through the points
	spline.update();
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
//	target.draw(background);

	target.draw(spline);

	for (size_t i = 0; i < circles.size(); i++)
	{
		target.draw(*circles[i]);
	}
}