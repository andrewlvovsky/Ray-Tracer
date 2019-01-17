#ifndef __SHADER_H__
#define __SHADER_H__

#include "vec.h"
class Render_World;
class Ray;

extern bool debug_pixel;

class Shader
{
public:
    Render_World& world;

    Shader(Render_World& world_input)
        :world(world_input)
    {}

    virtual ~Shader()
    {}

    virtual vec3 Shade_Surface(const Ray& ray,const vec3& intersection_point,
        const vec3& normal,int recursion_depth) const=0;
};
#endif
