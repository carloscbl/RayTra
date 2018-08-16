#pragma once
#include "Ray.hpp"
#include "vec3.hpp"


class shape
{
public:
	double refraction = 1;

	virtual ~shape() {};

	virtual vec3<double> Intersection(Ray r, bool& hits) = 0;
};