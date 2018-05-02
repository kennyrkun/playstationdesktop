#include "Background.hpp"

#define WIDTH 1080
#define HEIGHT 720

Background::Background()
{

	backgroundTexture.loadFromFile("./psdk/background.jpg");
	background.setTexture(&backgroundTexture);

	spline.setThickness(5);
	spline.setColor(sf::Color::Black);

	maxSplinePosition = 100;
	minSplinePosition = HEIGHT - 100;
	middleSplinePosition = HEIGHT / 2;

	std::vector<sf::Vector2f> vertices;

	// TODO: amount of points depending on how wide the window is
	const int numberOfPoints = 10;
	for (size_t i = 0; i < 10; i++)
	{
		vertices.push_back(sf::Vector2f(50.f + (108.f * i), HEIGHT / 2));
	}

	spline.addVertices(0, vertices);
	spline.setBezierInterpolation(); // enable Bezier spline
	spline.setInterpolationSteps(10); // curvature resolution

	for (size_t i = 0; i < spline.getVertexCount(); i++)
	{
		sf::CircleShape* cir = new sf::CircleShape(5);
		circles.push_back(cir);
	}

	for (size_t i = 0; i < spline.getHandlesVisible(); i++)
	{
		anim.addTask(spline[i].position.y, maxSplinePosition, EaseType::CircEaseOut, 0, true);
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
	target.draw(background);

	target.draw(spline);

	for (size_t i = 0; i < circles.size(); i++)
	{
		target.draw(*circles[i]);
	}
}