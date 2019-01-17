#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "object.h"
class Sphere : public Object
{
    vec3 center;
    double radius;

public:
    Sphere(const vec3& center_input,double radius_input)
        :center(center_input),radius(radius_input)
    {}

    virtual Hit Intersection(const Ray& ray, int part) const override;
    virtual vec3 Normal(const vec3& point, int part) const override;
    virtual Box Bounding_Box(int part) const override;
};
#endif
