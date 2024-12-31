#pragma once
#ifndef CONFIGURATION_MODE_HPP
#define CONFIGURATION_MODE_HPP

#include "app_mode.hpp"
#include "raylib_utilities.hpp"
#include <random>
#include <string>
#include <cmath>

class ConfigurationMode : public app::AppModeBase {
public:
    ConfigurationMode(std::shared_ptr<render::Scene> scene):
        app::AppModeBase(scene),
        m_cam{0},
        m_rd{},
        m_random{m_rd()}
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
        return {};
    }

    void update() override {
        UpdateCamera(&m_cam, CAMERA_FIRST_PERSON);
        m_cam.up = (Vector3){0, 1, 0};
        if (IsKeyPressed(KEY_BACKSPACE)) {
            random_scene();
        } else if (IsKeyPressed(KEY_ONE)) {
            sphere_scene();
        } else if (IsKeyPressed(KEY_TWO)) {
            cube_scene();
        }
    }

    void draw() override {
        char* s_properties = (char*)TextFormat(
            "Speed of sound: %.3f m/s\nAtmospheric Density: %.3fkg/m^3\nAcoustic Impedance: %.3fkg/(m^2 * s)",
            m_scene->environment().atmosphere.speed_of_sound,
            m_scene->environment().atmosphere.density,
            m_scene->environment().atmosphere.acoustic_impedance()
        );

        BeginMode3D(m_cam);
            // // Dereferencing the scene shared pointer is causing a runtime exception
            for (const auto object : m_scene->objects()) {
                object.display();
            }

            DrawGrid(50, 1.0);
            DrawRay(Ray({0, 0, 0}, {1, 0, 0}), RED);    // X
            DrawRay(Ray({0, 0, 0}, {0, 1, 0}), GREEN);  // Y
            DrawRay(Ray({0, 0, 0}, {0, 0, 1}), BLUE);   // Z

            
        EndMode3D();

        DrawText(s_properties,  GetScreenWidth() - MeasureText(s_properties, ui::TEXT_ROW_HEIGHT) - ui::BORDER_SPACING, ui::BORDER_SPACING, ui::TEXT_ROW_HEIGHT, BLACK);

    }

    void random_scene() {
        m_scene->clear();
        std::uniform_int_distribution<int> random_integer_generator(0, 1);
        std::uniform_int_distribution<uint8_t> random_color_val_generator(0, 255);
        std::uniform_real_distribution<double> random_double_genenerator(0.05, 1);
        // Add random objects in random places
        for (int i=0; i < 8; i++) {
            auto type = random_integer_generator(m_random);
            auto location = render::Vector3{
                random_double_genenerator(m_random) * 20 - 10,
                random_double_genenerator(m_random) * 20,
                random_double_genenerator(m_random) * 20 - 10
            };
            auto scale = render::Vector3{
                random_double_genenerator(m_random) * 5,
                random_double_genenerator(m_random) * 5,
                random_double_genenerator(m_random) * 5
            };
            auto rotation = QuaternionFromAxisAngle(
                {
                    random_double_genenerator(m_random),
                    random_double_genenerator(m_random),
                    random_double_genenerator(m_random)
                },
                random_double_genenerator(m_random) * PI);
            switch (type) {
                case 0:
                    m_scene->add(Cube(location,
                                    scale,
                                    rotation,
                                    render::Material{
                                        {random_color_val_generator(m_random),
                                         random_color_val_generator(m_random),
                                         random_color_val_generator(m_random),
                                         255},
                                         random_double_genenerator(m_random)
                                    }));
                    break;
                case 1:
                    m_scene->add(Sphere(location,
                                      scale,
                                      rotation,
                                      render::Material{
                                        {random_color_val_generator(m_random),
                                         random_color_val_generator(m_random),
                                         random_color_val_generator(m_random),
                                         255},
                                         random_double_genenerator(m_random)
                                      }));
                    break;
            }
        }


    }

    void sphere_scene() {
        m_scene->clear();
        m_scene->add(
            Sphere(Vector3{0, 0, 0},
                   Vector3{0.5, 0.5, 0.5},
                   Quaternion{1, 0, 0, 0},
                   render::Material{
                        {200, 200, 200, 255},
                        700,
                        3850
                   })
        );
    }

    void cube_scene() {
        m_scene->clear();
        m_scene->add(
            Cube(Vector3{0, 0, 0},
                 Vector3{1, 1, 1},
                 Quaternion{1, 0, 0, 0},
                 render::Material{
                      {200, 200, 200, 255},
                      700,
                      3850
                })
        );
    }


private:
    Camera m_cam;
    std::random_device m_rd;
    std::mt19937 m_random;


};


#endif // CONFIGURATION_MODE_HPP