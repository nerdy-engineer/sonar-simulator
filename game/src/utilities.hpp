#pragma once
#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "ray.hpp"
#include "vec3.hpp"
#include "color.hpp"
#include <cmath>
#include <limits>
#include <memory>
#include <stdint.h>

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}




#endif // UTILITIES_HPP