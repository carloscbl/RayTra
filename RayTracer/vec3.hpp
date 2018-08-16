#pragma once

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
