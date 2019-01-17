#ifndef __PLANE_H__
#define __PLANE_H__

#include "object.h"

class Plane : public Object
{
public:
    vec3 x1;
    vec3 normal;

    Plane(const vec3& point,const vec3& normal)
        :x1(point),normal(normal.normalized())
    {}

    virtual Hit Intersection(const Ray& ray, int part) const override;
    virtual vec3 Normal(const vec3& point, int part) const override;
    virtual Box Bounding_Box(int part) const override;
};
#endif
