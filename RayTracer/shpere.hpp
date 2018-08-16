#pragma once
#include "vec3.hpp"
#include "shape.hpp"

class sphere : public shape{
public:
	double rad = 0;
	vec3<double> pos;
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
		vec3<double> hitpoint = r.origin;
		vec3<double> trans = r.dir;
		trans = trans * t ;
		hitpoint = hitpoint + trans;
		return hitpoint;
	}
	sphere(double rad, vec3<double> && pos) :rad(rad), pos(pos) { refraction = 1.33; };

};