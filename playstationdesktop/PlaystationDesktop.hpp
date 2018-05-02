#ifndef DESKTOP_HPP
#define DESKTOP_HPP

#include "AnimationManager.hpp"
#include "Interpolate.hpp"
#include "LoadingClock.hpp"
#include "Background.hpp"

struct ApplicationSettings
{
	std::string desktop_binary_directory;

	sf::Vector2f windowSize = sf::Vector2f(1080, 720);
};

class PlaystationDesktop
{
public:
	PlaystationDesktop(ApplicationSettings settings);
	~PlaystationDesktop();

	void start();
	void shutdown();

	void HandleEvents();
	void Update();
	void Draw();

	bool running() { return isRunning;  }

private:
	bool isRunning;

	ApplicationSettings appSettings;

	sf::Text statustext;
	sf::Font font;

	LoadingClock clock;
	Background background;

	sf::RenderWindow window;
};

#endif // !DESKTOP_HPP