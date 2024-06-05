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
#include "utilities.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "camera.hpp"


namespace render {

struct frame_t {
    int w;
    int h;
    color4<uint8_t>* pixels;
};


class Raytracer {
public:
    Raytracer(frame_t frame_description) :
    // Raytracer(frame_t frame_description) :
        m_frame{frame_description},
        m_cam{1, {m_frame.w, m_frame.h}, 2.8, {0, 0, 0}},
        m_world{nullptr}
    {
        resize(m_frame);
    }

    void add_world(std::shared_ptr<hit::hittable_list> world) {
        m_world = world;
    }

    bool render() {
        if (m_frame.pixels == nullptr) {
            return false;
        }
        double r, g, b;
        for (int x=0; x < m_frame.w; x++) {
            for (int y=0; y < m_frame.h; y++) {
                // r = double(y) / (m_frame.w - 1);
                // g = double(x) / (m_frame.h - 1);
                // b = 0;
                auto ray = m_cam.get_ray(x, y);
                auto c = ray_color(ray);
                // m_frame.pixels[x*m_frame.w + y] = {uint8_t(r*255.999), uint8_t(g*255.999), uint8_t(0*255.999), 255};
                m_frame.pixels[y*m_frame.w + x] = {uint8_t(c.r*255.999), uint8_t(c.g*255.999), uint8_t(c.b*255.999), uint8_t(c.a*255.999)};
            }
        }
        return true;
    }

    color4<double> ray_color(const ray& r) {
        hit_record rec;
        if (m_world->hit(r, 0, infinity, rec)) {
            return promote(0.5*(rec.normal + color3<double>{1, 1, 1}));
        }
        
        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return promote((1.0-a)*color3<double>{1.0, 1.0, 1.0} + a*color3<double>{0.5, 0.7, 1.0});
    }

    void resize(frame_t new_frame) {
        m_frame = new_frame;
        m_cam.set_resolution({m_frame.w, m_frame.h});
    }

private:
    frame_t m_frame;
    Camera m_cam;
    std::shared_ptr<hit::hittable_list> m_world;
    

};


}



#endif