#pragma once
#include <utility>
#include <vector>

template<typename T>
class vec3
{
public:
	T x, y, z;
	vec3(T x, T y, T z) : x(x), y(y), z(z) {};

	auto operator+(vec3 r) {
		return vec3(x + r.x, y + r.y, z + r.z);
	}
	static auto operator+(vec3 lhs, vec3 rhs) {
		return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	auto operator*(float r) {
		return vec3(x*r, y*r, z*r);
	}
	static auto operator*(vec3 v, float r) {
		return vec3(v.x*r, v.y*r, v.z*r);
	}

	//dot
	auto operator%(vec3 r) {
		return x * r.x + y * r.y + z * r.z;
	}
	static auto operator%(vec3 lhs,vec3 rhs) {
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	//cross
	auto operator^(vec3 r) {
		return vec3(y*r.z - z * r.y, z*r.x - x * r.z, x*r.y - y * r.x);
	}
	static auto operator^(vec3 lhs,vec3 rhs) {
		return vec3(lhs.y*rhs.z - lhs.z * rhs.y, lhs.z*rhs.x - lhs.x * rhs.z, lhs.x*rhs.y - lhs.y * rhs.x);
	}
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
	plane_black_white_dimensions square_dimension;
	const vec3<double> pos;

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
	const vec3<double> pos;
	const vec3<double> dir;
	Camera(vec3<double> && pos, vec3<double> && dir) :pos(pos),dir(dir) {};
private:

};

class ray
{
public:
	const vec3<double> origin;
	const vec3<double> dir;
	const double lenght;

	ray(vec3<double> && startPosition, vec3<double> && dir, double lenght) : 
		origin(startPosition),
		dir(dir),
		lenght(lenght)
	{};
	~ray();

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
	int half_px = (PX_bounds::height * PX_bounds::width) / 2;

	void calc_factor(vec3<double> && v) {
		double z_ = pix_size / v.z;
	}

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
	void shoot() {
		//This shoot the rays for every pix

	};
	void process_matrix();
	~Render();
};

