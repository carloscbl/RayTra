#pragma once
#include <utility>
#include <vector>
#include <algorithm>
#include <memory>

#include "plane.hpp"
#include "vec3.hpp"
#include "shpere.hpp"
#include "shape.hpp"
#include "camera.hpp"
#include "Ray.hpp"

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
	std::vector<uint8_t> screen_matrix;
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
		return vec3<double>(
			camera.pos.x + screenPX_to_world_space(px,Dimension::x),
			camera.pos.y + screenPX_to_world_space(px, Dimension::y),
			camera.pos.z);
	}
	
	void traze() {
		for (int px = 0; px < screen_matrix.size(); ++px) {
			auto initial_ray = Ray(world_px_pos(px),vec3<double>(0,0,-1));
			uint8_t add = 0;
			for (auto & element : shapes)
			{
				bool got_color_yet = false;
				Ray bounce = initial_ray;
				for (size_t i = 0; i < max_ray_bounces; i++)
				{
					bool hit = false;
					auto hitPoint = element->Intersection(bounce, hit);
					if (hit && element->refraction > 1.1)
					{
						//bounce
						Ray r = Ray(std::move(hitPoint), std::move(refract(hitPoint, bounce.dir, element->refraction)));
						bounce = r;
						add = 128;
					}
					else if (hit) {
						//without 
						if (add != 0)
						{
							screen_matrix[px] = add;
						}
						else {
							screen_matrix[px] = std::static_pointer_cast<plane>(element)->getColor(hitPoint, (hitPoint.z - camera.pos.z) / 2);
						}
						got_color_yet = true;
						break;
					}
					else {
						//no hit
						break;
					}
				}
				if (got_color_yet)
				{
					break;
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

