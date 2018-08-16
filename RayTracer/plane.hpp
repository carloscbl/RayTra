#pragma once
#include "vec3.hpp"
#include "shape.hpp"


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
	
	plane(vec3<double> && pos, vec3<double> && dir) : pos(pos),dir(dir) {};
	
	vec3<double> Intersection(Ray r, bool& hits) override {
		double d = this->dir.dot(r.dir);
		if ( std::fabs(d) > 0.0001)
		{
			double t = (this->pos - r.origin).dot(this->dir) / d;
			if (t >= 0)
			{
				hits = true;
			}
			vec3<double> hitpoint = r.origin + r.dir * t;

			return hitpoint;
		}
		hits = false;
		return vec3<double>(0,0,0);
	}
	
	int getColor(const vec3<double>& pos, double scale) const{

		//(bool)Floor(pos.x / scala) % 2;
		//This is not correct since we are scaling the read of the color, the ray collision should be the corrected already
		int a = (int)std::floor(pos.x * scale) % 2;
		int b = (int)std::floor(pos.y * scale) % 2;
		
		bool white = false;


		if ( a )
		{
			white = true;
		}
		else {
			white = false;
		}
		if (b)
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


};