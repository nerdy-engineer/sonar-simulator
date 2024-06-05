#pragma once
#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include <stdint.h>
#include <iostream>
#include "color.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "camera.hpp"
#include "primitives.hpp"


namespace render {

struct frame_t {
    int w;
    int h;
    color4<uint8_t>* pixels;
};


class Raytracer {
public:
    Raytracer(frame_t frame_description) :
        frame{frame_description},
        cam{1, {frame.w, frame.h}, 2.8, {0, 0, 0}}
    {
        resize(frame);
    }

    bool render() {
        if (frame.pixels == nullptr) {
            return false;
        }
        double r, g, b;
        for (int x=0; x < frame.w; x++) {
            for (int y=0; y < frame.h; y++) {
                // r = double(y) / (frame.w - 1);
                // g = double(x) / (frame.h - 1);
                // b = 0;
                auto ray = cam.get_ray(x, y);
                auto c = ray_color(ray);
                // frame.pixels[x*frame.w + y] = {uint8_t(r*255.999), uint8_t(g*255.999), uint8_t(0*255.999), 255};
                frame.pixels[y*frame.w + x] = {uint8_t(c.r*255.999), uint8_t(c.g*255.999), uint8_t(c.b*255.999), uint8_t(c.a*255.999)};
            }
        }
        return true;
    }

    color4<double> ray_color(const ray& r) {
        auto t = hit::hit_sphere(point3(0, 0, -1), 0.5, r);
        if (t > 0.0) {
            vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
            return promote(0.5*color3<double>{N.x() + 1, N.y() + 1, N.z() + 1});
            // return {t/2.0, t/2.0, t/2.0, 1.0};
        }


        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return promote((1.0-a)*color3<double>{1.0, 1.0, 1.0} + a*color3<double>{0.5, 0.7, 1.0});
    }

    void resize(frame_t new_frame) {
        frame = new_frame;
        cam.set_resolution({frame.w, frame.h});
    }

private:
    frame_t frame;
    Camera cam;
    

};


}



#endif