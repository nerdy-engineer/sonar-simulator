#pragma once
#ifndef APP_HPP
#define APP_HPP

#include "raylib.h"
#include "raymath.h"
#include <utility>
#include <string>
#include <exception>
#include <stdint.h>
#include <iostream>
#include <memory>
#include "ui_constants.hpp"
#include "configuration_mode.hpp"
#include "scene.hpp"
#include "object.hpp"


class App {
public:
    enum State {
        PREVIEW,
        RENDER,
        CONFIGURE,
        LOADING
    };

    App(std::pair<int, int> window_size, int fps, std::string window_caption) :
        app_state_{State::CONFIGURE},
        window_size_{window_size},
        pixels{nullptr},
        img_{},
        tex_{},
        m_scene{std::make_shared<render::Scene>()},
        m_configurator{m_scene}
        // m_camera{0}
    {
        InitWindow(window_size_.first, window_size_.second, window_caption.c_str());
        resize(window_size_);
        for (uint32_t i = 0; i < img_.width * img_.height; i++) { pixels[i] = {255, 255, 255, 255}; }
        tex_ = LoadTextureFromImage(img_);
        DisableCursor();
        SetTargetFPS(fps);
        // m_scene->add(Sphere({0, 0, 0}, {1, 1, 1}, {1, 0, 0, 0}));
        m_scene->add(Cube({0, 0.5, 0}, {1, 1, 1}, QuaternionFromAxisAngle({1, 0, 0}, PI/4)));

        // m_camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
        // m_camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        // m_camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
        // m_camera.fovy = 45.0f;
        // m_camera.projection = CAMERA_PERSPECTIVE;
    }

    void state(State new_state) {
        if (new_state != app_state_) {
            app_state_ = new_state;
            // Trigger state change handler?
        }
    }

    bool app_should_close() {
        return WindowShouldClose();
    }

    void update() {
        m_configurator.update();
    }

    void draw() {
        BeginDrawing();
        ClearBackground(WHITE);
		switch (app_state_) {
            case State::CONFIGURE:
                m_configurator.draw();
                DrawText("Configuration", ui::BORDER_SPACING, ui::BORDER_SPACING, ui::TEXT_ROW_HEIGHT, BLACK);                
                break;
            case State::LOADING:
                DrawText("Loading", ui::BORDER_SPACING, ui::BORDER_SPACING, ui::TEXT_ROW_HEIGHT, BLACK);
                break;
            case State::PREVIEW:
                DrawText("Preview", ui::BORDER_SPACING, ui::BORDER_SPACING, ui::TEXT_ROW_HEIGHT, BLACK);
                break;
            case State::RENDER:
                DrawText("Render", ui::BORDER_SPACING, ui::BORDER_SPACING, ui::TEXT_ROW_HEIGHT, BLACK);
                break;
        }
		DrawFPS(ui::BORDER_SPACING, ui::BORDER_SPACING + ui::TEXT_ROW_HEIGHT);
		EndDrawing();
    }

    void process_input() {
        if (IsKeyDown(KEY_F7)) {
            // Configure mode
            state(State::CONFIGURE);
        } else if (IsKeyDown(KEY_F8)) {
            // Preview Mode
            state(State::PREVIEW);
        } else if (IsKeyDown(KEY_F9)) {
            // Render Mode
            state(State::RENDER);
        }
    }

    void resize(std::pair<int, int> window_size) {
        window_size_ = window_size;
        RL_FREE(pixels);
        pixels = (Color*)RL_MALLOC(window_size.first * window_size.second * sizeof(Color));
        if (pixels == nullptr) {
            // This is a problem...
            throw std::exception();
        }
        // frame_t frame = {window_size.first, window_size.second, 1e6, 18, (render::color4<uint8_t>*)pixels};
        img_.data = pixels;
        img_.width = window_size.first;
        img_.height = window_size.second;
        img_.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
        img_.mipmaps = 1;
    }

    ~App() {
        UnloadImage(img_);
        UnloadTexture(tex_);
        CloseWindow();
    }

private:
    State app_state_;
    std::pair<int, int> window_size_;
    Color *pixels;
    Image img_;
    Texture2D tex_;
    std::shared_ptr<render::Scene> m_scene;
    ConfigurationMode m_configurator;
    // Camera3D m_camera;



};


#endif