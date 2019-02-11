#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <vector>
#include "box.h"
#include "vec.h"

// t has to be bigger than small_t to register an intersection with a ray.  You
// may need to tweak this value.
// http://stackoverflow.com/questions/17688360/ray-tracing-shadow-bug
static const double small_t = 1e-4;
extern bool debug_pixel;

class Ray;
class Shader;
class Object;

struct Hit
{
    const Object* object; // object that was intersected
    double dist; // distance along ray to intersection location
    int part; // which part was intersected (eg, for meshes)
};

class Object
{
public:
    Shader* material_shader;

    // the number of parts that this object contains.
    int number_parts;

    Object() :material_shader(0), number_parts(1) {}
    virtual ~Object() {}

    // Check for an intersection against the ray.  If there was an
    // intersection, record the distance to the first intersection.
    // If an intersection was found, the object structure member
    // should be set to this.  If no intersection was found, the
    // object member should be set to NULL.
    // Do not return intersections where dist<small_t.
    // If part>=0 only test for intersections against the specified part.
    // If part<0 intersect against all parts.
    // For meshes, the part structure attribute should be set to the
    // index of the triangle that was intersected.  For other types of
    // objects, the part attribute can be ignored.
    virtual Hit Intersection(const Ray& ray, int part) const=0;

    // Return the normal.  For objects with multiple parts (meshes), you
    // will need to use part to determine which piece was intersected.
    // It will be set to the part structure entry returned from the
    // intersection routine.
    virtual vec3 Normal(const vec3& point, int part) const=0;

    // If part>=0, return the bounding box for the specified part.
    // If part<0, return the bounding box for the whole object.
    virtual Box Bounding_Box(int part) const=0;
};
#endif
