#ifndef DESKTOP_HPP
#define DESKTOP_HPP

#include "AnimationManager.hpp"
#include "Interpolate.hpp"
#include "LoadingClock.hpp"
#include "Background.hpp"

class Desktop
{
public:
	Desktop();
	~Desktop();

	void start();
	void shutdown();

	void HandleEvents();
	void Update();
	void Draw();

private:
	sf::Text statustext;

	sf::RenderWindow window;
};

#endif // !DESKTOP_HPP