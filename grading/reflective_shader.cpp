#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color = shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);

    vec3 v_ray = ray.direction;
    vec3 r_dir = 2.0 * dot(-v_ray, normal) * normal + v_ray;
    Ray r_ray(intersection_point, r_dir);

    if(recursion_depth < world.recursion_depth_limit) {
        color = (1 - reflectivity) * color + reflectivity * world.Cast_Ray(r_ray, ++recursion_depth);
    }
    else
        color = (1-reflectivity) * color;

    return color;
}
