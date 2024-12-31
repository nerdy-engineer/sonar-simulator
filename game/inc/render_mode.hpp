#pragma once
#ifndef RENDER_MODE_HPP
#define RENDER_MODE_HPP

#include "app_mode.hpp"
#include <thread>


class RenderMode : public app::AppModeBase {
public:
    RenderMode(std::shared_ptr<render::Scene> scene) :
        app::AppModeBase(scene)
    {

    }

    void update() override {
        // If the renderer isn't actively rendering, then kick off a new thread to render in parallel

    }

    void draw() override {
        // Draw the render buffer
    }


private:


};

#endif // RENDER_MODE_HPP