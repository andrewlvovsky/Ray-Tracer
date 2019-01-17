#ifndef __RENDER_WORLD_H__
#define __RENDER_WORLD_H__

#include <vector>
#include "camera.h"
#include "hierarchy.h"
#include "object.h"

class Light;
class Shader;
class Ray;

class Render_World
{
public:
    Camera camera;

    Shader *background_shader;
    std::vector<Object*> objects;
    std::vector<Light*> lights;
    vec3 ambient_color;
    double ambient_intensity;

    bool enable_shadows;
    int recursion_depth_limit;

    Hierarchy hierarchy;

    Render_World();
    ~Render_World();

    void Render_Pixel(const ivec2& pixel_index);
    void Render();
    void Initialize_Hierarchy();

    vec3 Cast_Ray(const Ray& ray,int recursion_depth);
    Hit Closest_Intersection(const Ray& ray);
};
#endif
