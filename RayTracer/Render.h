#pragma once
#include <utility>
template<typename T>
class vec3
{
public:
	T x, y, z;
	vec3(T x, T y, T z) : x(x), y(y), z(z) {};

	auto operator+(vec3 r) {
	return vector3(x + r.x, y + r.y, z + r.z);
	}

	auto operator*(float r) {
		return vec3(x*r, y*r, z*r);
	}

	auto operator%(vec3 r) {
		return x * r.x + y * r.y + z * r.z;
	}

	auto operator^(vec3 r) {
		return vec3(y*r.z - z * r.y, z*r.x - x * r.z, x*r.y - y * r.x);
	}

private:

};

class sphere {
public:
	double rad = 0;
	vec3<double> pos;
	const double refraction = 1.33;

	sphere(double rad, vec3<double> && pos) :rad(rad), pos(pos) {};

};
class plane {
public:
	struct plane_black_white_dimensions
	{
		const double height = 0.1;
		const double width = 0.1;
	};
	double rad = 0;
	vec3<double> pos;
	const double refraction = 1.33;

	sphere(double rad, vec3<double> && pos) :rad(rad), pos(pos) {};

};

class Render
{
public:
	struct PX_bounds
	{
	public:
		const int height = 1000;
		const int width = 1000;

	};
	
	sphere sphere;

	Render(): sphere(0.02, std::move(vec3<double>(0, 0, 0.04))) {};
	~Render();
};

