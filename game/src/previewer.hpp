#pragma once
#ifndef PREVIEWER_HPP
#define PREVIEWER_HPP

#include <memory>
#include "raylib.h"
#include "scene.hpp"
#include "material.hpp"
#include "objects.hpp"
#include "camera.hpp"



class Previewer {
public:
    Previewer(render::Scene& scene) :
        m_scene{std::make_shared<render::Scene>(scene)},
        m_camera{0}
    {

    }

    void setup_camera() {
        m_camera.position = (Vector3){0, -1, 0};
        m_camera.target = (Vector3){0, 0, 0};
        m_camera.up = (Vector3){0, 0, 1};
        m_camera.fovy = 45.0;
        m_camera.projection = CAMERA_PERSPECTIVE;
        SetTargetFPS(60);
    }

    void draw() {
        BeginMode3D(m_camera);
        for (const auto object : m_scene->objects()) {
            auto position = object->position();
            auto up = object->up();
            auto direction = object->direction();
            auto scale = object->scale();
            auto color = object->material().albedo()*255;
            Vector3 obj_position = (Vector3){position.x(), position.y(), position.z()};
            Color obj_color = {int(color.r), int(color.g), int(color.b), 255};

            // Set up object transform before drawing the shape:
            switch (object->shape()) {
                case render::GeometryType::SPHERE:
                    DrawSphere(obj_position, 0.5, obj_color);
                    break;
                case render::GeometryType::DISC:
                    DrawCylinder(obj_position, 0.5, 0.5, 0, 1, obj_color);
                    break;
                case render::GeometryType::PLANE:
                    DrawPlane(obj_position, (Vector2){1000, 1000}, obj_color);
                    break;
            }
        }
        EndMode3D();
        
    }



private:
    std::shared_ptr<render::Scene> m_scene;
    Camera m_camera;

};


#endif // PREVIEWER_HPP