#ifndef __PHONG_SHADER_H__
#define __PHONG_SHADER_H__

#include "shader.h"

class Phong_Shader : public Shader
{
public:
    vec3 color_ambient,color_diffuse,color_specular;
    double specular_power;

    Phong_Shader(Render_World& world_input,
        const vec3& color_ambient,
        const vec3& color_diffuse,
        const vec3& color_specular,
        double specular_power)
        :Shader(world_input),color_ambient(color_ambient),
        color_diffuse(color_diffuse),color_specular(color_specular),
        specular_power(specular_power)
    {}

    virtual vec3 Shade_Surface(const Ray& ray,const vec3& intersection_point,
        const vec3& normal,int recursion_depth) const override;
};
#endif
