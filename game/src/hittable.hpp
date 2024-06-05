#pragma once
#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "utilities.hpp"


namespace render {

class hit_record {
public:
    point3 p;
    vec3 normal;
    double t;
    double front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        // Sets the hit record normal vector.
        // Note: the parameter `outward_normal` is assumed to have unit length.

        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }

};


class hittable {
public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};



}

#endif // HITTABLE_HPP