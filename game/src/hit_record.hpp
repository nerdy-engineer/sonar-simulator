#pragma once
#ifndef HIT_RECORD_HPP
#define HIT_RECORD_HPP

#include "utilities.hpp"

namespace render {

struct hit_record {
    point3 p;
    vec3 normal;
    double t;
    double front_face;
    double f_factor = 1;    // f_o/f_s = v/(v+v_s) Multiply the transmit frequency by this factor to get the frequency after the bounce
    double amplitude = 1;   // This value is modified by the sensor sensitivity at that angle and the reflectivity of the material
    double distance_traveled = 0;
    color4<double> color = {1, 1, 1, 1};
    void set_face_normal(const ray& r, const vec3& outward_normal) {
        // Sets the hit record normal vector.
        // Note: the parameter `outward_normal` is assumed to have unit length.

        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

}

#endif // HIT_RECORD_HPP