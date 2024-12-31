#pragma once
#ifndef RAYLIB_UTILITIES_HPP
#define RAYLIB_UTILITIES_HPP

#include "raylib.h"
#include "raymath.h"


void operator-(Vector3& lhs, const Vector3& rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
}

Vector3 operator-(const Vector3& single) {
    return {-single.x, -single.y, -single.z};
}

void operator+(Vector3& lhs, const Vector3& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
}


#endif // RAYLIB_UTILITIES_HPP