#pragma once
#include <utility>
#include <vector>

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

	const vec3 operator-(const vec3 r) const {
		return vec3(x - r.x, y - r.y, z - r.z);
	}
	static auto substract(vec3 lhs, vec3 rhs) {
		return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	auto operator*(float r) const {
		return vec3(x*r, y*r, z*r);
	}
	static auto mult(vec3 v, float r)  {
		return vec3(v.x*r, v.y*r, v.z*r);
	}

	//dot
	auto operator%(vec3 r) const {
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
	double lenght;

	Ray(vec3<double> && startPosition, vec3<double> && dir, double lenght) : 
		origin(startPosition),
		dir(dir),
		lenght(lenght)
	{};
	~Ray();

	//0 -> black, 1 -> white | Similar to turned off, turned on
	//const int get_black_white_color() {

	//}

};

class shape
{
public:
	const double refraction = 1;
	shape();
	virtual ~shape();

	virtual vec3<double> Intersection(Ray r, bool* hits) = 0;
};

class sphere : public shape{
public:
	double rad = 0;
	vec3<double> pos;
	const double refraction = 1.33;
	vec3<double> Intersection(Ray r, bool* hits) {
		// math

		float a = r.dir % r.dir;
		vec3<double> sphereToRay = r.origin - pos;
		float b = 2 * (r.dir % sphereToRay);
		float c = (sphereToRay % sphereToRay) - pow(rad, 2);


		float dis = pow(b, 2) - 4 * a * c;

		if (dis < 0) {
			*hits = false;
			return vec3<double>(0, 0, 0);
		}

		float root = sqrt(dis);

		float oneRoot = (((-1 * b) + root)) / (2 * a);
		float otherRoot = (((-1 * b) - root)) / (2 * a);

		float t = -1;
		if (oneRoot >= 0 && otherRoot >= 0) {
			t = otherRoot;
		}
		else if (oneRoot >= 0) {
			t = oneRoot;
		}
		else {
			*hits = false;
			return vec3<double>(0, 0, 0);
		}

		*hits = true;
		vec3<double> pt = r.origin;
		vec3<double> trans = r.dir;
		trans = trans * t ;
		pt = pt + trans;
		return pt;
	}
	sphere(double rad, vec3<double> && pos) :rad(rad), pos(pos) {};

};
class plane {
public:
	struct plane_black_white_dimensions
	{
		const double height = 0.1;
		const double width = 0.1;
	};
	plane_black_white_dimensions square_dimension;
	vec3<double> pos;

	const int getColor(const vec3<double> & pos) const noexcept {
		if (true)
		{

		}
	}

	plane(vec3<double> && pos) : pos(pos) {};

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
	
	sphere sphere;
	plane plane;
	Camera camera;
	double pix_size = 1 / PX_bounds::height;
	std::vector<int> screen_matrix;
	std::vector<int> screen_buffer;
	int half_px = (PX_bounds::height * PX_bounds::width) / 2;

	Render(): 
		sphere(0.02, std::move(vec3<double>(0, 0, 0.04))),
		plane( std::move(vec3<double>(0,0,0)) ),
		camera(std::move(vec3<double>(0, 0, 0.25)) , std::move(vec3<double>(0, 0, -1))),
		screen_matrix(PX_bounds::height * PX_bounds::width)
	{};
	enum Dimension
	{
		x,y,z
	};
	int normalize_px(int px, Dimension d) {
		if (d == Dimension::x)
		{
			int col_normalized = px % PX_bounds::width;
			int offset_center = col_normalized - (PX_bounds::width / 2) ;
			return offset_center / 1000;
		}
		else
		{
			int r = ((px + half_px) - (half_px * 2)) / (half_px * 2);
		}
	}
	vec3<double>world_px_pos(int px) {
		return vec3<double>(
			camera.pos.x + normalize_px(px,Dimension::x) * pix_size,
			camera.pos.y + normalize_px(px, Dimension::y) * pix_size,
			camera.pos.z);
	}
	void traze() {
		for (const auto & px : screen_matrix) {
			Ray(world_px_pos(px),vec3<double>(0,0,-1),1);
		}
		//This shoot the rays for every pix

	};
	void process_matrix();
	~Render();
};

