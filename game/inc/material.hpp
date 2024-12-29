#pragma once
#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "raylib.h"

namespace render {

typedef struct Material {
    Color albedo = {0, 0, 0, 255};
    double absorbption = 1.0;



};

}

#endif // MATERIAL_HPP