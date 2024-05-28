#pragma once
#ifndef APP_HPP
#define APP_HPP

#include "raylib.h"
#include <utility>
#include <string>
#include "raytracer.hpp"
#include <exception>
#include <stdint.h>
#include <iostream>


class App {
public:
    enum State {
        PREVIEW,
        RENDER,
        CONFIGURE,
        LOADING
    };

    App(std::pair<int, int> window_size, std::string window_caption) :
        app_state_{State::RENDER},
        window_size_{window_size},
        pixels{nullptr},
        render_engine{{window_size.first, window_size.second, (render::color4<uint8_t>*)pixels}},
        img_{},
        tex_{}
    {
        InitWindow(window_size_.first, window_size_.second, window_caption.c_str());
        resize(window_size_);
        for (uint32_t i = 0; i < img_.width * img_.height; i++) { pixels[i] = {255, 255, 255, 255}; }
        tex_ = LoadTextureFromImage(img_);
    }

    void state(State new_state) {
        app_state_ = new_state;
    }

    bool app_should_close() {
        return WindowShouldClose();
    }

    void draw() {
        BeginDrawing();

		switch (app_state_) {
            case State::CONFIGURE:
                configure();
                break;
            case State::LOADING:
                loading();
                break;
            case State::PREVIEW:
                loading();
                break;
            case State::RENDER:
                render();
                break;
        }
		
		EndDrawing();
    }

    void loading() {
		ClearBackground(BLACK);
        DrawText("Loading...", 200,200,20,WHITE);
    }

    void preview() {
        ClearBackground(BLACK);
        DrawText("Preview...", 200,200,20,WHITE);
    }

    void render() {
        // ClearBackground(WHITE);
        render_engine.render();
        
        UpdateTexture(tex_, img_.data);
        
        DrawTexture(tex_, 0, 0, {255, 255, 255, 255});
        
        DrawText("Render...", 25, 25, 20, WHITE);
    }

    void configure() {
        ClearBackground(GRAY);
        DrawText("Configure...", 200,200,20,WHITE);
    }

    void resize(std::pair<int, int> window_size) {
        window_size_ = window_size;
        RL_FREE(pixels);
        pixels = (Color*)RL_MALLOC(window_size.first * window_size.second * sizeof(Color));
        if (pixels == nullptr) {
            // This is a problem...
            throw std::exception();
        }
        render_engine.resize({window_size.first, window_size.second, (render::color4<uint8_t>*)pixels});
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
    render::Raytracer render_engine;
    Image img_;
    Texture2D tex_;




};


#endif