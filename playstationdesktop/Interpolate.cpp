#include "Interpolate.hpp"

#include <iostream>

#define PI 3.14

#define LOG 0

#if LOG
#define LOGG std::cout << __FUNCTION__ << std::endl;
#else
#define LOGG //
#endif

float Interpolate::Quint::easeIn(float t, float b, float c, float d)
{
	LOGG

	return c * (t /= d) * t * t * t * t + b;
}

float Interpolate::Quint::easeOut(float t, float b, float c, float d)
{
	LOGG

	return c * ((t = t / d - 1) * t * t * t * t + 1) + b;
}

float Interpolate::Quint::easeInOut(float t, float b, float c, float d)
{
	LOGG

	if ((t /= d / 2) < 1)
		return c / 2 * t * t * t * t * t + b;

	return c / 2 * ((t -= 2) * t * t * t * t + 2) + b;
}

float Interpolate::Back::easeIn(float t, float b, float c, float d)
{
	LOGG

	float s = 1.70158f;
	float postFix = t /= d;
	return c * (postFix)*t*((s + 1)*t - s) + b;
}

float Interpolate::Back::easeOut(float t, float b, float c, float d)
{
	LOGG
		float s = 1.70158f;
	return c * ((t = t / d - 1)*t*((s + 1)*t + s) + 1) + b;
}

float Interpolate::Back::easeInOut(float t, float b, float c, float d)
{
	LOGG

	float s = 1.70158f;
	if ((t /= d / 2) < 1)
		return c / 2 * (t * t * (((s *= (1.525f)) + 1) * t - s)) + b;

	float postFix = t -= 2;
	return c / 2 * ((postFix)* t * (((s *= (1.525f)) + 1) * t + s) + 2) + b;
}

float Interpolate::Sine::easeIn(float t, float b, float c, float d)
{
	LOGG

	return -c * cos(t / d * (PI / 2)) + c + b;
}

float Interpolate::Sine::easeOut(float t, float b, float c, float d)
{
	LOGG

	return c * sin(t / d * (PI / 2)) + b;
}

float Interpolate::Sine::easeInOut(float t, float b, float c, float d)
{
	LOGG

	return -c / 2 * (cos(PI * t / d) - 1) + b;
}

float Interpolate::Linear::easeNone(float t, float b, float c, float d)
{
	LOGG

	return c * t / d + b;
}

float Interpolate::Linear::easeIn(float t, float b, float c, float d)
{
	LOGG

	return c * t / d + b;
}

float Interpolate::Linear::easeOut(float t, float b, float c, float d)
{
	LOGG
		
	return c * t / d + b;
}

float Interpolate::Linear::easeInOut(float t, float b, float c, float d)
{
	LOGG
	
	return c * t / d + b;
}

float Interpolate::Quart::easeIn(float t, float b, float c, float d)
{
	LOGG

	return c * (t /= d) * t * t * t + b;
}

float Interpolate::Quart::easeOut(float t, float b, float c, float d)
{
	LOGG
	
	return -c * ((t = t / d - 1) * t * t * t - 1) + b;
}

float Interpolate::Quart::easeInOut(float t, float b, float c, float d)
{
	LOGG

		if ((t /= d / 2) < 1) return c / 2 * t * t * t * t + b;
	return -c / 2 * ((t -= 2) * t * t * t - 2) + b;
}

float Interpolate::Quad::easeIn(float t, float b, float c, float d)
{
	LOGG

	return c * (t /= d) *t + b;
}

float Interpolate::Quad::easeOut(float t, float b, float c, float d)
{
	LOGG

	return -c * (t /= d) * (t - 2) + b;
}

float Interpolate::Quad::easeInOut(float t, float b, float c, float d)
{
	LOGG

	if ((t /= d / 2) < 1)
		return ((c / 2) * (t * t)) + b;

	return -c / 2 * (((t - 2) * (--t)) - 1) + b;
	/*
	originally return -c/2 * (((t-2)*(--t)) - 1) + b;

	I've had to swap (--t)*(t-2) due to diffence in behaviour in
	pre-increment operators between java and c++, after hours of joy
	*/
}

float Interpolate::Expo::easeIn(float t, float b, float c, float d)
{
	LOGG

	return (t == 0) ? b : c * pow(2, 10 * (t / d - 1)) + b;
}

float Interpolate::Expo::easeOut(float t, float b, float c, float d)
{
	LOGG

	return (t == d) ? b + c : c * (-pow(2, -10 * t / d) + 1) + b;
}

float Interpolate::Expo::easeInOut(float t, float b, float c, float d)
{
	LOGG

	if (t == 0)
		return b;
	if (t == d)
		return b + c;

	if ((t /= d / 2) < 1)
		return c / 2 * pow(2, 10 * (t - 1)) + b;

	return c / 2 * (-pow(2, -10 * --t) + 2) + b;
}

float Interpolate::Elastic::easeIn(float t, float b, float c, float d)
{
	LOGG

	if (t == 0) return b;  if ((t /= d) == 1) return b + c;
	float p = d * .3f;
	float a = c;
	float s = p / 4;
	float postFix = a * pow(2, 10 * (t -= 1)); // this is a fix, again, with post-increment operators
	return -(postFix * sin((t * d - s) * (2 * PI) / p)) + b;
}

float Interpolate::Elastic::easeOut(float t, float b, float c, float d)
{
	LOGG

	if (t == 0) return b;  if ((t /= d) == 1) return b + c;
	float p = d * .3f;
	float a = c;
	float s = p / 4;
	return (a * pow(2, -10 * t) * sin((t * d - s) * (2 * PI) / p) + c + b);
}

float Interpolate::Elastic::easeInOut(float t, float b, float c, float d)
{
	LOGG

	if (t == 0)
		return b;
	if ((t /= d / 2) == 2)
		return b + c;

	float p = d * (.3f * 1.5f);
	float a = c;
	float s = p / 4;

	if (t < 1)
	{
		float postFix = a * pow(2, 10 * (t -= 1)); // postIncrement is evil
		return -.5f * (postFix * sin((t * d - s) * (2 * PI) / p)) + b;
	}

	float postFix = a * pow(2, -10 * (t -= 1)); // postIncrement is evil
	return postFix * sin((t * d - s) * (2 * PI) / p) * .5f + c + b;
}

float Interpolate::Cubic::easeIn(float t, float b, float c, float d)
{
	LOGG

	return c * (t /= d) * t * t + b;
}

float Interpolate::Cubic::easeOut(float t, float b, float c, float d)
{
	LOGG

	return c * ((t = t / d - 1) * t * t + 1) + b;
}

float Interpolate::Cubic::easeInOut(float t, float b, float c, float d)
{
	LOGG

	if ((t /= d / 2) < 1)
		return c / 2 * t * t * t + b;

	return c / 2 * ((t -= 2) * t * t + 2) + b;
}

float Interpolate::Bounce::easeIn(float t, float b, float c, float d)
{
	LOGG

	return c - easeOut(d - t, 0, c, d) + b;
}

float Interpolate::Bounce::easeOut(float t, float b, float c, float d)
{
	LOGG

	if ((t /= d) < (1 / 2.75f))
	{
		return c * (7.5625f * t * t) + b;
	}
	else if (t < (2 / 2.75f))
	{
		float postFix = t -= (1.5f / 2.75f);
		return c * (7.5625f * (postFix)* t + .75f) + b;
	}
	else if (t < (2.5 / 2.75))
	{
		float postFix = t -= (2.25f / 2.75f);
		return c * (7.5625f * (postFix)* t + .9375f) + b;
	}
	else
	{
		float postFix = t -= (2.625f / 2.75f);
		return c * (7.5625f * (postFix)* t + .984375f) + b;
	}
}

float Interpolate::Bounce::easeInOut(float t, float b, float c, float d)
{
	LOGG

	if (t < d / 2)
		return easeIn(t * 2, 0, c, d) * .5f + b;
	else
		return easeOut(t * 2 - d, 0, c, d) * .5f + c * .5f + b;
}

float Interpolate::Circ::easeIn(float t, float b, float c, float d)
{
	LOGG

	return -c * (sqrt(1 - (t /= d) * t) - 1) + b;
}

float Interpolate::Circ::easeOut(float t, float b, float c, float d)
{
	LOGG

	return c * sqrt(1 - (t = t / d - 1) * t) + b;
}

float Interpolate::Circ::easeInOut(float t, float b, float c, float d)
{
	LOGG

	if ((t /= d / 2) < 1)
		return -c / 2 * (sqrt(1 - t * t) - 1) + b;

	return c / 2 * (sqrt(1 - t * (t -= 2)) + 1) + b;
}
