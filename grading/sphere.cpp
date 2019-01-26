#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    double discriminant = pow(dot(ray.direction, ray.endpoint - center), 2) - (dot(ray.direction, ray.direction) * (dot(ray.endpoint - center, ray.endpoint - center) - pow(radius, 2)));
    double t_1 = 0;
    double t_2 = 0;

    if (discriminant > 0) {
        t_1 = -dot(ray.direction, ray.endpoint - center) + sqrt(discriminant) / dot(ray.direction, ray.direction);
        t_2 = -dot(ray.direction, ray.endpoint - center) - sqrt(discriminant) / dot(ray.direction, ray.direction);

        if (t_1 < t_2 && t_1 >= small_t) {
            return {this, t_1, part};
        }
        else if (t_1 >= t_2 && t_2 >= small_t){
            return {this, t_2, part};
        }
    }

    return {nullptr, t_1, part};
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    normal = (point - center) / radius;
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
