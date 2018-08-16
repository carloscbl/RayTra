#pragma once
#include "vec3.hpp"

class Ray
{
public:
	vec3<double> origin;
	vec3<double> dir;

	Ray(vec3<double> && startPosition, vec3<double> && dir) : 
		origin(startPosition),
		dir(dir)
	{};
	~Ray() {};

	//0 -> black, 1 -> white | Similar to turned off, turned on
	//const int get_black_white_color() {

	//}

};
