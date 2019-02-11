#ifndef __MESH_H__
#define __MESH_H__

#include "object.h"

// Consider a hit to be inside a triange if all barycentric weights
// satisfy weight>=-weight_tol
static const double weight_tol = 1e-4;

class Mesh : public Object
{
    std::vector<vec3> vertices;
    std::vector<ivec3> triangles;
    Box box;
    
public:
    Mesh()
    {}

    virtual Hit Intersection(const Ray& ray, int part) const override;
    virtual vec3 Normal(const vec3& point, int part) const override;
    bool Intersect_Triangle(const Ray& ray, int tri, double& dist) const;
    void Read_Obj(const char* file);
    Box Bounding_Box(int part) const override;
};
#endif
