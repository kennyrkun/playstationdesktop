#ifndef ANIMATION_MANAGER_HPP
#define ANIMATION_MANAGER_HPP

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#define EASE_SLOWEST .0075f
#define  EASE_SLOWER .01f
#define    EASE_SLOW .025f
#define     EASE_MED .05f
#define    EASE_FAST .075f
#define  EASE_FASTER .25f
#define EASE_FASTEST .50f

// TODO: move this into it's own file or into AnimationManager.cpp
class ARotation
{
public:
	ARotation(sf::RectangleShape &shape, float &target, float ease, bool constant);
	~ARotation();

	float originalRotation;
	float currentRotation;
	float &targetRotation;

	float ease;

	bool isDoing = true;
	bool constant;

	sf::RectangleShape& shape;

	void Update();
};

class AnimationManager
{
public:
	AnimationManager();

	~AnimationManager();

	void addTask(sf::RectangleShape& shape, float &rotation, float ease, bool constant = false);

	void clearTasks();

	void Update();

//	sf::Clock tickClock;
//	sf::Time timeSinceLastUpdate = sf::Time::Zero;
//	sf::Time duration = sf::Time::Zero;
//	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	std::vector<ARotation*> tasks;
};

#endif // !ANIMATION_MANAGER_HPP
