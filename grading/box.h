#ifndef __BOX_H__
#define __BOX_H__

#include "ray.h"
#include "misc.h"
#include <limits>

class Box
{
public:
    // lowermost and uppermost corners of bounding box
    vec3 lo,hi;

    // Return whether the ray intersects this box.
    bool Intersection(const Ray& ray) const;

    // Compute the smallest box that contains both *this and bb.
    Box Union(const Box& bb) const;

    // Enlarge this box (if necessary) so that pt also lies inside it.
    void Include_Point(const vec3& pt);

    // Create a box to which points can be correctly added using Include_Point.
    void Make_Empty();
};
#endif
