#include "AnimationManager.hpp"

#include "Interpolate.hpp"

// animation task

AnimatedTask::~AnimatedTask()
{
	// do nothing
}

// this is kind of nasty
// FIXME: we need other ways to specific rotation
// TODO: figure out how to deal with rotations beyond 360 d

AnimatedRotation::AnimatedRotation(sf::Shape &shape, float& targetRotation, std::function<float(float, float, float, float)> easeFunction, int duration, bool constant, int ID) : shape(shape), targetRotation(targetRotation), easeFunction(easeFunction), duration(duration), constant(constant), animationID(ID)
{
	std::cout << "arot " << animationID << std::endl;

	originalRotation = shape.getRotation();

	changeInRotation = targetRotation - originalRotation;

	tick.restart();
}

AnimatedRotation::~AnimatedRotation()
{
	shape.setRotation(targetRotation);

	std::cout << "darot " << animationID << std::endl;
}

// TODO: better method for figuring out if it's done
bool AnimatedRotation::pastTime()
{
	return tick.getElapsedTime().asMilliseconds() < duration;
}

void AnimatedRotation::Update()
{
	shape.setRotation(easeFunction(tick.getElapsedTime().asMilliseconds(), originalRotation, changeInRotation, duration));
};

// AnimatedTranslation

AnimatedTranslation::AnimatedTranslation(sf::Shape &shape, sf::Vector2f destinationPosition, std::function<float(float, float, float, float)> easeFunction, int duration, bool constant, int ID) : shape(shape), targetPosition(destinationPosition), easeFunction(easeFunction), duration(duration), constant(constant), animationID(ID)
{
	std::cout << "atran " << animationID << std::endl;

	originalPosition = shape.getPosition();
	changeInPosition = destinationPosition - originalPosition;

	int x = destinationPosition.x - originalPosition.x;
	int y = destinationPosition.y - originalPosition.y;

	changeInPosition = sf::Vector2f(x, y);

	std::cout << "destin: " << destinationPosition.x << ", " << destinationPosition.y << std::endl;
	std::cout << "moving: " << changeInPosition.x << ", " << changeInPosition.y << std::endl;

	tick.restart();

	// TODO: make sure it's not already at this position
}

AnimatedTranslation::~AnimatedTranslation()
{
	shape.setPosition(targetPosition);

	std::cout << "datran " << animationID << std::endl;
}

bool AnimatedTranslation::pastTime()
{
	return tick.getElapsedTime().asMilliseconds() < duration;
}

void AnimatedTranslation::Update()
{
	sf::Time t1 = tick.getElapsedTime();

	// we've gone past the time it should have taken
	if (t1.asMilliseconds() > duration)
		t1 = sf::milliseconds(duration);

	float x, y;

	x = easeFunction(t1.asMilliseconds(), originalPosition.x, changeInPosition.x, duration);
	y = easeFunction(t1.asMilliseconds(), originalPosition.y, changeInPosition.y, duration);

	shape.setPosition(sf::Vector2f(x, y));

//	std::cout << t1.asMilliseconds() << ", " << duration << "(" << x << ", " << y << ")" << std::endl;
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

std::function<float(float, float, float, float)> getEaseFunc(EaseType ease)
{
	std::function<float(float, float, float, float)> easeFunction;

	if (ease ==  EaseType::BackEaseIn)
		easeFunction = &Interpolate::Back::easeIn;
	else if (ease == EaseType::BackEaseOut)
		easeFunction = &Interpolate::Back::easeOut;
	else if (ease == EaseType::BackEaseInOut)
		easeFunction = &Interpolate::Back::easeInOut;
	else if (ease == EaseType::BounceEaseIn)
		easeFunction = &Interpolate::Bounce::easeIn;
	else if (ease == EaseType::BounceEaseOut)
		easeFunction = &Interpolate::Bounce::easeOut;
	else if (ease == EaseType::BounceEaseInOut)
		easeFunction = &Interpolate::Bounce::easeInOut;
	else if (ease == EaseType::CircEaseIn)
		easeFunction = &Interpolate::Circ::easeIn;
	else if (ease == EaseType::CircEaseOut)
		easeFunction = &Interpolate::Circ::easeOut;
	else if (ease == EaseType::CircEaseInOut)
		easeFunction = &Interpolate::Circ::easeInOut;
	else if (ease == EaseType::CubicEaseIn)
		easeFunction = &Interpolate::Cubic::easeIn;
	else if (ease == EaseType::CubicEaseOut)
		easeFunction = &Interpolate::Cubic::easeOut;
	else if (ease == EaseType::CubicEaseInOut)
		easeFunction = &Interpolate::Cubic::easeInOut;
	else if (ease == EaseType::ElasticEaseIn)
		easeFunction = &Interpolate::Elastic::easeIn;
	else if (ease == EaseType::ElasticEaseOut)
		easeFunction = &Interpolate::Elastic::easeOut;
	else if (ease == EaseType::ElasticEaseInOut)
		easeFunction = &Interpolate::Elastic::easeInOut;
	else if (ease == EaseType::ExpoEaseIn)
		easeFunction = &Interpolate::Expo::easeIn;
	else if (ease == EaseType::ExpoEaseOut)
		easeFunction = &Interpolate::Expo::easeOut;
	else if (ease == EaseType::ExpoEaseInOut)
		easeFunction = &Interpolate::Expo::easeInOut;
	else if (ease == EaseType::LinearEaseNone)
		easeFunction = &Interpolate::Linear::easeNone;
	else if (ease == EaseType::LinearEaseIn)
		easeFunction = &Interpolate::Linear::easeIn;
	else if (ease == EaseType::LinearEaseOut)
		easeFunction = &Interpolate::Linear::easeOut;
	else if (ease == EaseType::LinearEaseInOut)
		easeFunction = &Interpolate::Linear::easeInOut;
	else if (ease == EaseType::QuartEaseIn)
		easeFunction = &Interpolate::Quart::easeIn;
	else if (ease == EaseType::QuartEaseOut)
		easeFunction = &Interpolate::Quart::easeOut;
	else if (ease == EaseType::QuartEaseInOut)
		easeFunction = &Interpolate::Quart::easeInOut;
	else if (ease == EaseType::QuadEaseIn)
		easeFunction = &Interpolate::Quad::easeIn;
	else if (ease == EaseType::QuadEaseOut)
		easeFunction = &Interpolate::Quad::easeOut;
	else if (ease == EaseType::QuadEaseInOut)
		easeFunction = &Interpolate::Quad::easeInOut;
	else if (ease == EaseType::QuintEaseIn)
		easeFunction = &Interpolate::Quint::easeIn;
	else if (ease == EaseType::QuintEaseOut)
		easeFunction = &Interpolate::Quint::easeOut;
	else if (ease == EaseType::QuintEaseInOut)
		easeFunction = &Interpolate::Quint::easeInOut;
	else
		std::cout << static_cast<int>(ease) << "is not a valid interpolation function" << std::endl;

	return easeFunction;
}

int AnimationManager::addTask(sf::Shape& shape, sf::Vector2f destination, EaseType ease, int duration, bool constant)
{
	AnimatedTranslation* task = new AnimatedTranslation(shape, destination, getEaseFunc(ease), duration, constant, tasks.size());

	tasks.push_back(task);

	// animation id needs to be assigned differently, because the
	// total size of the thing might change and we could end up
	// with multiple aniimations using the same id
	return tasks.back()->animationID;
}

int AnimationManager::addTask(sf::Shape& shape, float& targetRotation, EaseType ease, int duration, bool constant)
{
	AnimatedRotation* task = new AnimatedRotation(shape, targetRotation, getEaseFunc(ease), duration, constant, tasks.size());

	tasks.push_back(task);

	return tasks.back()->animationID;
}

void AnimationManager::clearTasks()
{
	for (size_t i = 0; i < tasks.size(); i++)
		delete tasks[i];
	tasks.clear();
}

void AnimationManager::Update()
{
	for (size_t i = 0; i < tasks.size(); i++)
	{
		tasks[i]->Update();

		if (!tasks[i]->constant && !tasks[i]->pastTime())
		{
			std::cout << "animation " << tasks[i]->animationID << " finished" << std::endl;

			delete tasks[i];
			tasks.erase(std::remove(tasks.begin(), tasks.end(), tasks[i]), tasks.end());
		}
	}
}
