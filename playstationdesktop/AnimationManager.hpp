#ifndef ANIMATION_MANAGER_HPP
#define ANIMATION_MANAGER_HPP

#include <SFML/Graphics.hpp>

#include <functional>
#include <iostream>
#include <vector>

enum EaseType
{
	BackEaseIn,
	BackEaseOut,
	BackEaseInOut,
	BounceEaseIn,
	BounceEaseOut,
	BounceEaseInOut,
	CircEaseIn,
	CircEaseOut,
	CircEaseInOut,
	CubicEaseIn,
	CubicEaseOut,
	CubicEaseInOut,
	ElasticEaseIn,
	ElasticEaseOut,
	ElasticEaseInOut,
	ExpoEaseIn,
	ExpoEaseOut,
	ExpoEaseInOut,
	LinearEaseNone,
	LinearEaseIn,
	LinearEaseOut,
	LinearEaseInOut,
	QuartEaseIn,
	QuartEaseOut,
	QuartEaseInOut,
	QuadEaseIn,
	QuadEaseOut,
	QuadEaseInOut,
	QuintEaseIn,
	QuintEaseOut,
	QuintEaseInOut
};

class AnimatedTask
{
public:
	virtual ~AnimatedTask() = 0;

	bool constant = false;

	int animationID = 0;

	virtual bool pastTime() = 0;

	virtual void Update() = 0;

private:
	std::function<float(float t, float b, float c, float d)> easeFunction;
};

// TODO: support rotation
class AnimatedRotation : public AnimatedTask
{
public:
	AnimatedRotation(sf::Shape &shape, float& targetRotation, std::function<float(float, float, float, float)> easeFunction, int duration, bool constant, int ID);
	~AnimatedRotation();

	int animationID;

	int duration; // miliseconds
	sf::Clock tick;

	bool pastTime();
	bool constant = false;

	sf::Shape& shape;

	float& targetRotation;
	float originalRotation;

	void Update();

private:
	float changeInRotation;

	std::function<float(float t, float b, float c, float d)> easeFunction;
};

class AnimatedTranslation : public AnimatedTask
{
public:
	AnimatedTranslation(sf::Shape &shape, sf::Vector2f targetPosition, std::function<float(float, float, float, float)> easeFunction, int duration, bool constant, int ID);
	~AnimatedTranslation();

	int animationID;

	int duration; // miliseconds
	sf::Clock tick;

	bool pastTime();
	bool constant = false;

	sf::Shape& shape;

	sf::Vector2f targetPosition;
	sf::Vector2f originalPosition;

	void Update();

private:
	sf::Vector2f changeInPosition;

	std::function<float(float t, float b, float c, float d)> easeFunction;
};

// Class for managing physical animations like translations and rotations
class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

	int addTask(sf::Shape& shape, sf::Vector2f destination, EaseType ease, int duration, bool constant = false);
	int addTask(sf::Shape& shape, float& targetRotation, EaseType ease, int duration, bool constant = false);

	void clearTasks();

	void Update();

//	sf::Clock tickClock;
//	sf::Time timeSinceLastUpdate = sf::Time::Zero;
//	sf::Time duration = sf::Time::Zero;
//	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	std::vector<AnimatedTask*> tasks;
};

#endif // !ANIMATION_MANAGER_HPP
