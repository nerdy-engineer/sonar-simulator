#pragma once
#ifndef RENDERER_UTILS_HPP
#define RENDERER_UTILS_HPP

// Common Headers
#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "interval.hpp"

struct frame_t {
    int w;
    int h;
    double sample_rate;
    double max_range;
    render::color4<uint8_t>* pixels;
};

#endif // RENDERER_UTILS_HPP