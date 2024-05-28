#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <utility>
#include "vec3.hpp"
#include "ray.hpp"

namespace render {

class Camera {
public:
    Camera(double focal_length, std::pair<int, int> res, point3 origin) :
        focal_length_{focal_length},
        resolution_{res},
        origin_{origin},
        center_pixel{},
        pixel_du{},
        pixel_dv{}
    {
        set_resolution(res);
    }

    void set_resolution(std::pair<int, int> res) {
        resolution_ = res;
        auto vpu = vec3(res.first, 0, 0);
        auto vpv = vec3(0, -res.second, 0);

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
    point3 origin_;
    point3 center_pixel;
    vec3 pixel_du;
    vec3 pixel_dv;


};

}

#endif