#ifndef __FLAT_SHADER_H__
#define __FLAT_SHADER_H__

#include "shader.h"

class Flat_Shader : public Shader
{
public:
    vec3 color;

    Flat_Shader(Render_World& world_input,const vec3& color=vec3(1,1,1))
        :Shader(world_input),color(color)
    {}

    virtual vec3 Shade_Surface(const Ray& ray,const vec3& intersection_point,
        const vec3& normal,int recursion_depth) const override;
};
#endif
