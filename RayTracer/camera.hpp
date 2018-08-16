#include "vec3.hpp"

class Camera
{
public:
	vec3<double> pos;
	vec3<double> dir;
	Camera(vec3<double> && pos, vec3<double> && dir) :pos(pos),dir(dir) {};
private:

};