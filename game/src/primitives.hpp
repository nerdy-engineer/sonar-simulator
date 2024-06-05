#pragma once
#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include "utilities.hpp"

namespace render {
namespace hit {

bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}





}
}

#endif // PRIMITIVES_HPP