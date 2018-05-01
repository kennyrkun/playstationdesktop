#ifndef INTERPOLATE_HPP
#define INTERPOLATE_HPP

/////////////////////////////////
//c++ port of Penner easing
//equations specifically with
//SFML in mind
//
//Adapted from c++ port by Jesus Gollonet
/////////////////////////////////

///////////////////////////////////////////
// t: time the function is called
// b: starting value being interpolated
// c: change in value
// d: duration
///////////////////////////////////////////

#include <cmath>

namespace Interpolate
{
	namespace Back
	{
		float easeIn(float t, float b, float c, float d);
		float easeOut(float t, float b, float c, float d);
		float easeInOut(float t, float b, float c, float d);
	}

	namespace Bounce
	{
		float easeIn(float t, float b, float c, float d);
		float easeOut(float t, float b, float c, float d);
		float easeInOut(float t, float b, float c, float d);
	}

	namespace Circ
	{
		float easeIn(float t, float b, float c, float d);
		float easeOut(float t, float b, float c, float d);
		float easeInOut(float t, float b, float c, float d);
	}

	namespace Cubic
	{
		float easeIn(float t, float b, float c, float d);
		float easeOut(float t, float b, float c, float d);
		float easeInOut(float t, float b, float c, float d);
	}

	namespace Elastic
	{
		float easeIn(float t, float b, float c, float d);
		float easeOut(float t, float b, float c, float d);
		float easeInOut(float t, float b, float c, float d);
	}

	namespace Expo
	{
		float easeIn(float t, float b, float c, float d);
		float easeOut(float t, float b, float c, float d);
		float easeInOut(float t, float b, float c, float d);
	}

	namespace Linear
	{
		float easeNone(float t, float b, float c, float d); // ??
		float easeIn(float t, float b, float c, float d);
		float easeOut(float t, float b, float c, float d);
		float easeInOut(float t, float b, float c, float d);
	}

	namespace Quart
	{
		float easeIn(float t, float b, float c, float d);
		float easeOut(float t, float b, float c, float d);
		float easeInOut(float t, float b, float c, float d);
	}

	namespace Quad
	{
		float easeIn(float t, float b, float c, float d);
		float easeOut(float t, float b, float c, float d);
		float easeInOut(float t, float b, float c, float d);
	}

	namespace Quint
	{
		float easeIn(float t, float b, float c, float d);
		float easeOut(float t, float b, float c, float d);
		float easeInOut(float t, float b, float c, float d);
	}

	namespace Sine
	{
		float easeIn(float t, float b, float c, float d);
		float easeOut(float t, float b, float c, float d);
		float easeInOut(float t, float b, float c, float d);
	}
}

#endif // INTERPOLATE_HPP
