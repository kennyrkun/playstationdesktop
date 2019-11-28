#ifndef ANIMATION_MANAGER_HPP
#define ANIMATION_MANAGER_HPP

#include <SFML/Graphics.hpp>

#include <map>
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

// base animation class
class AnimatedTask
{
public:
	virtual ~AnimatedTask() = 0;

	bool constant = false;

	int animationID = 0;

	// TODO: find a better way to do this
	virtual size_t getCurrent_st();
	virtual float getCurrent_f();
	virtual sf::Vector2f getCurrent_v2f();

	virtual bool pastTime() = 0;

	virtual void Update() = 0;

private:
	std::function<float(float t, float b, float c, float d)> easeFunction;
};

// class for animating numbers
class AnimatedNumber : public AnimatedTask
{
public:
	AnimatedNumber(size_t original, size_t target, std::function<float(float, float, float, float)> easeFunction, int duration, bool constant, int ID);
	~AnimatedNumber();

	int animationID;

	int duration; // miliseconds
	sf::Clock tick;

	// get the current value of the animated number
	size_t getCurrent() { return current; };

	bool pastTime();
	bool constant = false;

	size_t target;
	size_t original;

	void Update();

private:
	size_t changeInNumber;
	size_t current;

	std::function<float(float t, float b, float c, float d)> easeFunction;
};

// class for animating object's rotations
class AnimatedRotation : public AnimatedTask
{
public:
	AnimatedRotation(sf::Shape &shape, float targetRotation, std::function<float(float, float, float, float)> easeFunction, int duration, bool constant, int ID);
	~AnimatedRotation();

	int animationID;

	int duration; // miliseconds
	sf::Clock tick;

	float getCurrent() { return current; };

	bool pastTime();
	bool constant = false;

	sf::Shape& shape;

	float targetRotation;
	float originalRotation;

	void Update();

private:
	float changeInRotation;
	float current;

	std::function<float(float t, float b, float c, float d)> easeFunction;
};

// class for animating object's positions
class AnimatedTranslation : public AnimatedTask
{
public:
	AnimatedTranslation(sf::Shape &shape, sf::Vector2f targetPosition, std::function<float(float, float, float, float)> easeFunction, int duration, bool constant, int ID);
	~AnimatedTranslation();

	int animationID;

	int duration; // miliseconds
	sf::Clock tick;

	sf::Vector2f getCurrent() { return current; };

	bool pastTime();
	bool constant = false;

	sf::Shape& shape;

	sf::Vector2f targetPosition;
	sf::Vector2f originalPosition;

	void Update();

private:
	sf::Vector2f changeInPosition;
	sf::Vector2f current;

	std::function<float(float t, float b, float c, float d)> easeFunction;
};

// class for managing physical animations like translations and rotations
class PhysicalAnimator
{
public:
	PhysicalAnimator();
	~PhysicalAnimator();

	int addTranslationTask(sf::Shape& shape, sf::Vector2f destination, EaseType ease, int duration, bool constant = false);
	int addRotationTask(sf::Shape& shape, float& targetRotation, EaseType ease, int duration, bool constant = false);
	int addTask(size_t original, size_t target, EaseType ease, int duration, bool constant = false);

	void updateTaskTarget(size_t taskID, size_t newTarget);
	void updateTaskTarget(size_t taskID, sf::Vector2f newTarget);

	AnimatedTask* getTask(int taskID);

	void clearTask(int taskID);

	void clearTasks();

	void Update();

	bool working();
	
private:
	std::map<int, AnimatedTask*> tasks;
//	std::vector<AnimatedTask*> tasks;

	size_t totalAnimations;
};

#endif // !ANIMATION_MANAGER_HPP
