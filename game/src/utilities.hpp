#pragma once
#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <cmath>
#include <limits>
#include <memory>
#include <stdint.h>
#include <random>


// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    // Returns a random real in [0,1).
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}



// Common Headers
#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "interval.hpp"

struct frame_t {
    int w;
    int h;
    render::color4<uint8_t>* pixels;
};

#endif // UTILITIES_HPP