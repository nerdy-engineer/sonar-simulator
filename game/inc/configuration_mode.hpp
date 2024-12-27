#pragma once
#ifndef CONFIGURATION_MODE_HPP
#define CONFIGURATION_MODE_HPP

#include "app_mode.hpp"
#include "raylib_utilities.hpp"
#include <string>

class ConfigurationMode : public app::AppModeBase {
public:
    ConfigurationMode(std::shared_ptr<render::Scene> scene):
        app::AppModeBase(scene),
        m_cam{0}
    {
        setup_camera();
    }

    void setup_camera() {
        m_cam.position = (Vector3){0, 2, 10};
        m_cam.target = (Vector3){0, 0, 0};
        m_cam.up = (Vector3){0, 1, 0};  // Z is in/out, Y is up/down
        m_cam.fovy = 45.0;
        m_cam.projection = CAMERA_PERSPECTIVE;
        UpdateCamera(&m_cam, CAMERA_FIRST_PERSON);
    }

    std::string get_scene_json() const {
        // Need to return a json string
    }

    void update() override {
        UpdateCamera(&m_cam, CAMERA_FIRST_PERSON);
        m_cam.up = (Vector3){0, 1, 0};
    }

    void draw() override {
        // std::string debugString = "Scene is Null: ";
        // debugString += m_scene == nullptr ? "True" : "False";
        // DrawText(debugString.c_str(),
        //     GetRenderWidth() - ui::BORDER_SPACING - MeasureText(debugString.c_str(), ui::TEXT_ROW_HEIGHT),
        //     ui::TEXT_ROW_HEIGHT + ui::BORDER_SPACING,
        //     ui::TEXT_ROW_HEIGHT,
        //     BLACK);
        BeginMode3D(m_cam);
            // // Dereferencing the scene shared pointer is causing a runtime exception
            for (const auto object : m_scene->objects()) {
                object.display();
            }

            DrawGrid(1000, 1.0);
            // rlPushMatrix();
            //     rlRotatef(90, 1, 0, 0);
            //     // rlTranslatef(0, 0, ui::TEXT_ROW_HEIGHT*2);
            //     DrawText3D(GetFontDefault(), "+X", {100, 0, -2}, ui::TEXT_ROW_HEIGHT, 1, ui::TEXT_ROW_HEIGHT, true, BLACK);
            //     DrawText3D(GetFontDefault(), "-X", {-100, 0, -2}, ui::TEXT_ROW_HEIGHT, 1, ui::TEXT_ROW_HEIGHT, true, BLACK);
            //     DrawText3D(GetFontDefault(), "+Y", {0, 100, -2}, ui::TEXT_ROW_HEIGHT, 1, ui::TEXT_ROW_HEIGHT, true, BLACK);
            //     DrawText3D(GetFontDefault(), "-Y", {0, -100, -2}, ui::TEXT_ROW_HEIGHT, 1, ui::TEXT_ROW_HEIGHT, true, BLACK);
            //     DrawText3D(GetFontDefault(), "+Z", {0, 0, 100}, ui::TEXT_ROW_HEIGHT, 1, ui::TEXT_ROW_HEIGHT, true, BLACK);
            //     DrawText3D(GetFontDefault(), "-Z", {0, 0, -100}, ui::TEXT_ROW_HEIGHT, 1, ui::TEXT_ROW_HEIGHT, true, BLACK);
            // rlPopMatrix();
            DrawRay(Ray({0, 0, 0}, {1, 0, 0}), RED);    // X
            DrawRay(Ray({0, 0, 0}, {0, 1, 0}), GREEN);  // Y
            DrawRay(Ray({0, 0, 0}, {0, 0, 1}), BLUE);   // Z

            
        EndMode3D();

    }

private:
    Camera m_cam;


};


#endif // CONFIGURATION_MODE_HPP