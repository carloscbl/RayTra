#pragma once
#include <utility>
#include <vector>
#include <algorithm>
#include <memory>

template<typename T>
class vec3
{
public:
	T x, y, z;
	vec3(T x, T y, T z) : x(x), y(y), z(z) {};

	auto operator+(vec3 r) const {
		return vec3(x + r.x, y + r.y, z + r.z);
	}
	static auto add(vec3 lhs, vec3 rhs) {
		return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	auto operator-(const vec3 r) const {
		return vec3(x - r.x, y - r.y, z - r.z);
	}
	static auto substract(vec3 lhs, vec3 rhs) {
		return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	auto operator*(T r) const {
		return vec3(x*r, y*r, z*r);
	}
	static auto mult(vec3 v, T r)  {
		return vec3(v.x*r, v.y*r, v.z*r);
	}

	//dot
	const T dot(vec3 r) const  {
		return x * r.x + y * r.y + z * r.z;
	}
	static auto dot(vec3 lhs,vec3 rhs)  {
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	//cross
	auto operator^(vec3 r) const {
		return vec3(y*r.z - z * r.y, z*r.x - x * r.z, x*r.y - y * r.x);
	}
	static auto cross(vec3 lhs,vec3 rhs)  {
		return vec3(lhs.y*rhs.z - lhs.z * rhs.y, lhs.z*rhs.x - lhs.x * rhs.z, lhs.x*rhs.y - lhs.y * rhs.x);
	}
};

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

class shape
{
public:
	const double refraction = 1;

	virtual ~shape() {};

	virtual vec3<double> Intersection(Ray r, bool& hits) = 0;
};

class sphere : public shape{
public:
	double rad = 0;
	vec3<double> pos;
	const double refraction = 1.33;
	vec3<double> Intersection(Ray r, bool& hits) override {
		// math

		double a = r.dir.dot( r.dir);
		vec3<double> sphereToRay = r.origin - pos;
		double b = 2 * (r.dir.dot(sphereToRay));
		double c = (sphereToRay.dot(sphereToRay)) - pow(rad, 2);


		double dis = pow(b, 2) - 4 * a * c;

		if (dis < 0) {
			hits = false;
			return vec3<double>(0, 0, 0);
		}

		double root = sqrt(dis);

		double oneRoot = (((-1 * b) + root)) / (2 * a);
		double otherRoot = (((-1 * b) - root)) / (2 * a);

		double t = -1;
		if (oneRoot >= 0 && otherRoot >= 0) {
			t = otherRoot;
		}
		else if (oneRoot >= 0) {
			t = oneRoot;
		}
		else {
			hits = false;
			return vec3<double>(0, 0, 0);
		}

		hits = true;
		vec3<double> pt = r.origin;
		vec3<double> trans = r.dir;
		trans = trans * t ;
		pt = pt + trans;
		return pt;
	}
	sphere(double rad, vec3<double> && pos) :rad(rad), pos(pos) {};

};
class plane : public shape{
public:
	struct plane_black_white_dimensions
	{
		const double height = 0.1;
		const double width = 0.1;
	};
	plane_black_white_dimensions square_dimension;
	vec3<double> pos;
	vec3<double> dir;
	vec3<double> Intersection(Ray r, bool& hits) override {
		double d = this->dir.dot(r.dir);
		if ( std::fabs(d) > 0.0001)
		{
			double t = (this->pos - r.origin).dot(this->dir) / d;
			if (t >= 0)
			{
				hits = true;
			}
			vec3<double> hitPoint = r.origin + r.dir * t;
			return hitPoint;
		}
		hits = false;
		return vec3<double>(0,0,0);
	}
	int getColor(const vec3<double>& pos) const{
		int two_centimeter = 0.02 * 100;
		if (pos.x > 0.2)
		{
			int a = 7;
		}
		bool white = false;
		int a = (int)((pos.x+ 0.5) *100) % two_centimeter;
		int b = (int)((pos.y+ 0.5) *100) % two_centimeter;
		if ( a == 0 )
		{
			white = true;
		}
		else {
			white = false;
		}
		if (b == 0 )
		{
			white = !white;
		}

		if (white)
		{
			return 255;
		}
		else {
			return 0;
		}
	}

	plane(vec3<double> && pos, vec3<double> && dir) : pos(pos),dir(dir) {};

};
class Camera
{
public:
	vec3<double> pos;
	vec3<double> dir;
	Camera(vec3<double> && pos, vec3<double> && dir) :pos(pos),dir(dir) {};
private:

};



class Render
{
public:
	static struct PX_bounds
	{
	public:
		static constexpr int height = 1000;
		static constexpr int width = 1000;
	};

	const int max_ray_bounces = 4;
	std::vector<std::shared_ptr<shape>> shapes;
	Camera camera;
	double pix_size = 1.0 / PX_bounds::height;
	double pix_camera = pix_size / (camera.pos.z );
	std::vector<int> screen_matrix;
	int half_px = (PX_bounds::height * PX_bounds::width) / 2;

	Render(): 
		shapes(std::vector<std::shared_ptr<shape>>{
			std::make_shared<sphere>(0.02, std::move(vec3<double>(0, 0, 0.04))),
			std::make_shared<plane>( std::move(vec3<double>(0,0,0)), std::move(vec3<double>(0, 0, 1)) ),
		}),
		camera(std::move(vec3<double>(0, 0, 0.25)) , std::move(vec3<double>(0, 0, -1))),
		screen_matrix(PX_bounds::height * PX_bounds::width)
	{};
	enum Dimension
	{
		x,y,z
	};
	double screenPX_to_world_space(int px, Dimension d) {
		if (d == Dimension::x)
		{
			if (px > 1)
			{
				int i = 356;
			}
			int col_normalized = px % PX_bounds::width;
			int offset_center = col_normalized - (PX_bounds::width / 2) ;
			auto result = offset_center * pix_size;
			return result;
		}
		else
		{
			double r = ((px + half_px) - (half_px * 2.0)) / (half_px * 2.0);
			return r;
		}
	}
	vec3<double>world_px_pos(int px) {
		if (px > 500)
		{
			int i = 356;
		}
		return vec3<double>(
			camera.pos.x + screenPX_to_world_space(px,Dimension::x),
			camera.pos.y + screenPX_to_world_space(px, Dimension::y),
			camera.pos.z);
	}
	void traze() {
		for (int px = 0; px < screen_matrix.size(); ++px) {
			auto initial_ray = Ray(world_px_pos(px),vec3<double>(0,0,-1));
			for (auto & element : shapes)
			{
				Ray bounce = initial_ray;
				for (size_t i = 0; i < max_ray_bounces; i++)
				{
					bool hit = false;
					auto hitPoint = element->Intersection(bounce, hit);
					if (hit && element->refraction > 1.1)
					{
						//bounce
						bounce = Ray( std::move(hitPoint), std::move(refract(hitPoint,bounce.dir,element->refraction)));
					}
					else if (hit) {
						//without bounce
						screen_matrix[px] = std::static_pointer_cast<plane>(element)->getColor(hitPoint);
						break;
					}
					else {
						//no hit
						break;
					}
				}
			}
		}
		//This shoot the rays for every 
	};
	vec3<double> refract(vec3<double> origin, vec3<double> dir, double refraction_idx)
	{
		refraction_idx = 2.0f - refraction_idx;
		double cosi = dir.dot(origin);
		vec3<double> newDirection = (origin * refraction_idx - dir * (-cosi + refraction_idx * cosi));
		return newDirection;
	}

	~Render() {};
};

