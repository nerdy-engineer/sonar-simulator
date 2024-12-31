#pragma once
#ifndef HIT_RECORD_HPP
#define HIT_RECORD_HPP

#include "raylib.h"
#include "raymath.h"
#include "raylib_utilities.hpp"


namespace render {
typedef struct Color {
    double r;
    double g;
    double b;
    double a;
};

Color operator+(const Color& lhs, const Color& rhs) {
    return {lhs.r + rhs.r, lhs.g+rhs.g, lhs.b+rhs.b, std::max(lhs.a/rhs.a, 1.0)};
}

Color& operator+(Color& lhs, const Color& rhs) {
    lhs.r += rhs.r;
    lhs.g += rhs.g;
    lhs.b += rhs.b;
    lhs.a += rhs.a;
    lhs.a = std::max(lhs.a, 1.0);
    return lhs;
}

Color& operator+=(Color& lhs, const Color& rhs) {
    lhs.r += rhs.r;
    lhs.g += rhs.g;
    lhs.b += rhs.b;
    lhs.a += rhs.a;
    lhs.a = std::max(lhs.a, 1.0);
    return lhs;
}



typedef struct HitRecord {
    Vector3 hit_point;
    Vector3 normal;
    render::Color albedo;
    double ray_distance;
    double total_distance_traveled = 0;
    double frequency_dilation_factor = 1;
    double amplitude = 1;
    
    double front_face;
    void set_face_normal(const Ray& r, const Vector3& outward_normal) {
        // Sets the hit record normal vector.
        // Note: the parameter `outward_normal` is assumed to have unit length.
        front_face = Vector3DotProduct(r.direction, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }

};

}

#endif // HIT_RECORD_HPP