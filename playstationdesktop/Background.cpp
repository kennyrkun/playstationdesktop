#include "Background.hpp"

Background::Background() : rng(dev())
{
	/*
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(lower, upper);
	int i = dist(rng);
	*/

	backgroundTexture.loadFromFile("./psdk/background.jpg");
	background.setTexture(&backgroundTexture);

	spline.setThickness(100);
	spline.setColor(sf::Color::Black);

	std::vector<sf::Vector2f> vertices;

	// TODO: set color to 205, 205, 205

	// TODO: amount of points depending on how wide the window is
	const int numberOfPoints = 10;
	for (size_t i = 0; i < 10; i++)
		vertices.push_back(sf::Vector2f(50.f + (108.f * i), background.getSize().y / 2));

	spline.addVertices(0, vertices);
	spline.setBezierInterpolation(); // enable Bezier spline
	spline.setInterpolationSteps(10); // curvature resolution

	for (size_t i = 0; i < spline.getVertexCount(); i++)
	{
		sf::CircleShape* cir = new sf::CircleShape(5);
		cir->setOrigin(sf::Vector2f(2.5, 2.5));
		cir->setPosition(spline[i].position);
		circles.push_back(cir);
	}

	bool swap = false;
	for (size_t i = 0; i < spline.getVertexCount(); i++)
	{
		swap = !swap;
		anim.addTranslationTask(*circles[i], sf::Vector2f(circles[i]->getPosition().x, swap ? maxHeight : minHeight), EaseType::CircEaseOut, 10000, true);
	}
}

Background::~Background()
{
}

void Background::setSize(const sf::Vector2f& size)
{
	background.setSize(size);

	minHeight = 100;
	minHeight = size.y - 100;
}

void Background::HandleEvents(sf::Event& e)
{
}

void Background::Update()
{
	anim.Update();

	for (size_t i = 0; i < circles.size(); i++)
	{
		spline[i].position = circles[i]->getPosition();

		dist = std::uniform_int_distribution<std::mt19937::result_type>(minHeight, maxHeight);

		int min = dist(rng);
		int max= dist(rng);

		if (circles[i]->getPosition().y <= maxHeight)
			anim.addTranslationTask(*circles[i], sf::Vector2f(circles[i]->getPosition().x, min), EaseType::CubicEaseInOut, 10000, true);
		else if (circles[i]->getPosition().y >= minHeight)
			anim.addTranslationTask(*circles[i], sf::Vector2f(circles[i]->getPosition().x, max), EaseType::CubicEaseInOut, 10000, true);
	}

	spline.smoothHandles(); // automatically position handles to create a smooth curve that passes through the points
	spline.update();
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background);

	target.draw(spline);

	for (size_t i = 0; i < circles.size(); i++)
		target.draw(*circles[i]);
}