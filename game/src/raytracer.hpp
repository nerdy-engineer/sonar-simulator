#pragma once
#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include <stdint.h>
#include <iostream>
#include "scene.hpp"
#include "utilities.hpp"
#include "camera.hpp"
#include "primitives.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "world.hpp"
#include "camera.hpp"


namespace render {


class Raytracer {
public:
    Raytracer(frame_t frame_description) :
    // Raytracer(frame_t frame_description) :
        m_render_in_progress{false},
        m_frame{frame_description},
        m_cam{1, m_frame, 2.8, {0, 0, 0}},
        m_scene{}
        // m_world{nullptr}
    {
        resize(m_frame);
    }

    void set_scene(const Scene& scene) {
        m_scene = std::make_shared<const Scene>(scene);
    }

    // void add_world(std::shared_ptr<world> hittable_world) {
    //     m_world = hittable_world;
    // }

    bool render() {
        bool state = false;
        if (!m_render_in_progress) {
            m_render_in_progress = true;
            state = m_cam.render(m_scene);
        }
        return state;
    }

    void resize(frame_t& new_frame) {
        m_frame = new_frame;
        m_cam.set_resolution(m_frame);
    }

private:
    bool m_render_in_progress;
    frame_t m_frame;
    Camera m_cam;
    // std::shared_ptr<world> m_world;
    std::shared_ptr<const Scene> m_scene;
    

};


}



#endif