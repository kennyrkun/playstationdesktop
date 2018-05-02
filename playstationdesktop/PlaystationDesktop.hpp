#ifndef DESKTOP_HPP
#define DESKTOP_HPP

#include "AnimationManager.hpp"
#include "Interpolate.hpp"
#include "LoadingClock.hpp"
#include "Background.hpp"

class PlaystationDesktop
{
public:
	PlaystationDesktop();
	~PlaystationDesktop();

	void start();
	void shutdown();

	void HandleEvents();
	void Update();
	void Draw();

	bool running() { return isRunning;  }

private:
	bool isRunning;

	sf::Text statustext;
	sf::Font font;

	LoadingClock clock;
	Background background;

	sf::RenderWindow window;
};

#endif // !DESKTOP_HPP