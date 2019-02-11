#ifndef __BOUNDING_BOX_H__
#define __BOUNDING_BOX_H__

//#####################################################################
// Function #in
//#####################################################################
#include "object.h"
#include "ray.h"
#include "vec.h"

template<class T, int d>
vec<T,d> componentwise_max(const vec<T,d>& a, const vec<T,d>& b)
{
    vec<T,d> r;
    for(int i=0; i<d; i++) r[i] = std::max(a[i], b[i]);
    return r;
}

template<class T, int d>
vec<T,d> componentwise_min(const vec<T,d>& a, const vec<T,d>& b)
{
    vec<T,d> r;
    for(int i=0; i<d; i++) r[i] = std::min(a[i], b[i]);
    return r;
}

class Bounding_Box
{
public:
    // lowermost and uppermost corners of bounding box
    vec3 lo,hi;

    bool Intersection(const Ray& ray, double& dist);

    Bounding_Box Union(const Bounding_Box& bb) const;
};
#endif
