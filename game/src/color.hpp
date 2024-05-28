#pragma once
#ifndef COLOR_H
#define COLOR_H

namespace render {

template <typename T>
struct color {
    T r;
    T g;
    T b;
    T a;
};

}

#endif