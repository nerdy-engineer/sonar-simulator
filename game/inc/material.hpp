#pragma once
#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "raylib.h"

namespace render {

typedef struct Material {
    Color albedo = {255, 255, 255, 255};
    double density = 1.225;                 // Atmospheric density at STP = 1.225kg/m^3
    double speed_of_sound = 343;            // Speed of sound in air = 343m/s
    double acoustic_impedance() const { return density * speed_of_sound; }

};

double reflection(const Material& from, const Material& into) {
    auto z1 = from.acoustic_impedance();
    auto z2 = into.acoustic_impedance();
    auto term = ((z2 - z1)/(z2 + z1));
    return term*term;
}


}

#endif // MATERIAL_HPP