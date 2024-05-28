#pragma once
#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include <stdint.h>
#include <iostream>

namespace render {

template <typename T>
struct color {
    T r;
    T g;
    T b;
    T a;
};

struct frame_t {
    int w;
    int h;
    color<uint8_t>* pixels;
};


class Raytracer {
public:
    Raytracer(frame_t frame_description) :
        frame{frame_description}
    {
        
    }

    bool render() {
        if (frame.pixels == nullptr) {
            return false;
        }
        double r, g, b;
        for (int y=0; y < frame.w; y++) {
            for (int x=0; x < frame.h; x++) {
                r = double(y) / (frame.w - 1);
                g = double(x) / (frame.h - 1);
                b = 0;
                frame.pixels[x*frame.w + y] = {uint8_t(r*255.999), uint8_t(g*255.999), uint8_t(0*255.999), 255};
            }
        }
        return true;
    }

    void resize(frame_t new_frame) {
        frame = new_frame;
    }

private:
    
    frame_t frame;
    

};


}



#endif