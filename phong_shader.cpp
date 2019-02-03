#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    
    // I = (L_a * R_a) + (L_d * R_d * max(n*l, 0)) + (L_s * R_s * max(v*r, 0))

    // Ambient calculation
    vec3 ambient = world.ambient_color * world.ambient_intensity * this->color_ambient;

    color = ambient;

    // Adding diffuse and specular calculation to ambient
    vec3 diffuse, specular;

    for (auto light : world.lights) {
        vec3 l = light->position - intersection_point;  // light ray
        vec3 r = -l + 2 * dot(l, normal) * normal;  //reflection ray

        diffuse = this->color_diffuse * light->Emitted_Light(l);
        diffuse *= fmax(dot(normal, l.normalized()), 0.0);
        color += diffuse;

        specular = this->color_specular * light->Emitted_Light(l);
        specular *= pow(fmax(dot(-ray.direction, r.normalized()), 0.0), specular_power);
        color += specular;
    }

    return color;
}