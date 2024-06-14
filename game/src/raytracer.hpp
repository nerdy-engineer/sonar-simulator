#pragma once
#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include <stdint.h>
#include <iostream>
#include "utilities.hpp"
#include "camera.hpp"
#include "primitives.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "camera.hpp"


namespace render {


class Raytracer {
public:
    Raytracer(frame_t frame_description) :
    // Raytracer(frame_t frame_description) :
        m_frame{frame_description},
        m_cam{1, m_frame, 2.8, {0, 0, 0}},
        m_world{nullptr}
    {
        resize(m_frame);
    }

    void add_world(std::shared_ptr<hit::hittable_list> world) {
        m_world = world;
    }

    bool render() {
        return m_cam.render(*m_world);
    }

    void resize(frame_t& new_frame) {
        m_frame = new_frame;
        m_cam.set_resolution(m_frame);
    }

private:
    frame_t m_frame;
    Camera m_cam;
    std::shared_ptr<hit::hittable_list> m_world;
    

};


}



#endif