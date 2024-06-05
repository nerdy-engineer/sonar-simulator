#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <cmath>
#include <utility>
#include "vec3.hpp"
#include "ray.hpp"

namespace render {

class Camera {
public:
    Camera(double focal_length, std::pair<int, int> res, double sensor_size, point3 origin) :
        focal_length_{focal_length},
        resolution_{res},
        size_{sensor_size},
        origin_{origin},
        center_pixel{},
        pixel_du{},
        pixel_dv{}
    {
        // Sensor size is the diagonal size of the sensor receptive area
        set_resolution(res);
    }

    void set_resolution(std::pair<int, int> res) {
        resolution_ = res;
        // Aspect ratio = width/height
        // Diagonal to width ratio:
        // w^2 + h^2 = d^2
        // h = w/ar
        // w^2 + (w/ar)^2 = d^2
        // w^2 * (1 + ar^-2) = d^2
        // w^2 = d^2/(1 + ar^-2)
        double ar = double(res.first)/res.second;
        double viewport_width = sqrt((size_*size_) / (1 + 1/(ar*ar)));
        double viewport_height = viewport_width * (double(res.first)/res.second);;
        auto vpu = vec3(viewport_height, 0, 0);
        auto vpv = vec3(0, -viewport_width, 0);

        pixel_du = vpu/res.first;
        pixel_dv = vpv/res.second;

        auto vul = origin_ - vec3(0, 0, focal_length_) - vpu/2 - vpv/2;
        center_pixel = vul + 0.5* (pixel_du+pixel_dv);

    }


    ray get_ray(int x, int y) {     // Gets the ray corresponding to an x,y coordinate as you'd use for a rectangular camera
        auto pixel_center = x * pixel_du + y * pixel_dv + center_pixel;
        return ray(origin_, pixel_center);
    }

private:
    double focal_length_;
    std::pair<int, int> resolution_;
    double size_;
    point3 origin_;
    point3 center_pixel;
    vec3 pixel_du;
    vec3 pixel_dv;


};

}

#endif