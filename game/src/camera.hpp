#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <cmath>
#include <utility>
#include "vec3.hpp"
#include "ray.hpp"
#include "utilities.hpp"
#include "hittable.hpp"

namespace render {

class Camera {
public:
    Camera(double focal_length, frame_t frame, double sensor_size, point3 origin) :
        focal_length_{focal_length},
        frame_{},
        size_{sensor_size},
        origin_{origin},
        center_pixel{},
        pixel_00{},
        pixel_du{},
        pixel_dv{}
    {
        // Sensor size is the diagonal size of the sensor receptive area
        set_resolution(frame);
    }

    void set_resolution(frame_t& frame) {
        frame_ = frame;
        // Aspect ratio = width/height
        // Diagonal to width ratio:
        // w^2 + h^2 = d^2
        // h = w/ar
        // w^2 + (w/ar)^2 = d^2
        // w^2 * (1 + ar^-2) = d^2
        // w^2 = d^2/(1 + ar^-2)
        double ar = double(frame.w)/frame.h;
        double viewport_width = sqrt((size_*size_) / (1 + 1/(ar*ar)));
        double viewport_height = viewport_width * (double(frame.w)/frame.h);;
        auto vpu = vec3(viewport_height, 0, 0);
        auto vpv = vec3(0, -viewport_width, 0);

        pixel_du = vpu/frame.w;
        pixel_dv = vpv/frame.h;

        pixel_00 = origin_ - vec3(0, 0, focal_length_) - vpu/2 - vpv/2;
        center_pixel = pixel_00 + 0.5* (pixel_du+pixel_dv);

    }


    ray get_ray(int x, int y) {     // Gets the ray corresponding to an x,y coordinate as you'd use for a rectangular camera
        auto pixel_center = x * pixel_du + y * pixel_dv + center_pixel;
        return ray(origin_, pixel_center);
    }

    bool render(const hittable& world) {
        if (initialize()) {
            for (int j = 0; j < frame_.h; j++) {
                for (int i = 0; i < frame_.w; i++) {
                    auto pixel_center = pixel_00 + (i * pixel_du) + (j * pixel_dv);
                    auto ray_direction = pixel_center - origin_;
                    ray r(origin_, ray_direction);

                    auto p_color = ray_color(r, world);
                    frame_.pixels[j*frame_.w + i] = quantize(p_color);
                }
            }
            return true;
        }
        return false;
    }

private:
    bool initialize() {
        if (frame_.pixels == nullptr) {
            return false;
        }

        return true;
    }


    color4<double> ray_color(const ray& r, const hittable& world) const {
        hit_record rec;
        if (world.hit(r, interval(0, infinity), rec)) {
            return promote(0.5*(rec.normal + color3<double>{1, 1, 1}));
        }
        
        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return promote((1.0-a)*color3<double>{1.0, 1.0, 1.0} + a*color3<double>{0.5, 0.7, 1.0});
    }


    double focal_length_;
    frame_t frame_;
    double size_;
    point3 origin_;
    point3 center_pixel;
    point3 pixel_00;
    vec3 pixel_du;
    vec3 pixel_dv;


};

}

#endif