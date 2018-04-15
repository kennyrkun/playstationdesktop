#include "AnimationManager.hpp"

int spinTo(sf::Shape &shape, float rotation, float ease)
{
	if (static_cast<int>(shape.getRotation()) == static_cast<int>(rotation))
		return 1;

	float xx = (rotation - shape.getRotation()) * ease;
	shape.rotate(xx);
}

ARotation::ARotation(sf::RectangleShape &shape, float &target, float ease, bool constant) : shape(shape), targetRotation(target), ease(ease), constant(constant)
{
	std::cout << "arot" << std::endl;
}

ARotation::~ARotation()
{
	std::cout << "darot" << std::endl;
}

void ARotation::Update()
{
//	shape.rotate(10.f * interpolate::linear(duration.asSeconds(), 0.f, 1.f, 1.f), 0.f);
	currentRotation = shape.getRotation();

	if (spinTo(shape, targetRotation, ease) == 1)
		isDoing = false;
};


// animation manager

AnimationManager::AnimationManager()
{
	std::cout << "aman" << std::endl;
}

AnimationManager::~AnimationManager()
{
	for (size_t i = 0; i < tasks.size(); i++)
		delete tasks[i];
	tasks.clear();

	std::cout << "daman" << std::endl;
}

void AnimationManager::addTask(sf::RectangleShape& shape, float &rotation, float ease, bool constant)
{
	ARotation* task = new ARotation(shape, rotation, ease, constant);

	tasks.push_back(task);
}

void AnimationManager::clearTasks()
{
	for (size_t i = 0; i < tasks.size(); i++)
		delete tasks[i];
	tasks.clear();
}

void AnimationManager::Update()
{
//	timeSinceLastUpdate += tickClock.restart();
//	if (timeSinceLastUpdate > TimePerFrame)
//	{
//		timeSinceLastUpdate -= TimePerFrame;
//		duration += TimePerFrame;

	for (size_t i = 0; i < tasks.size(); i++)
	{
		tasks[i]->Update();

		if (!tasks[i]->constant && !tasks[i]->isDoing)
		{
			delete tasks[i];
			tasks.erase(std::remove(tasks.begin(), tasks.end(), tasks[i]), tasks.end());
		}
	}
//	}
}
