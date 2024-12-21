#pragma once
#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "vec3.hpp"

class Transform {
public:
    Transform(const render::vec3& location,
              const render::vec3& up,
              const render::vec3& direction,
              const render::vec3& scale) :
        m_location{location},
        m_up{up},
        m_direction{direction},
        m_scale{scale}
    {

    }

private:
    render::vec3 m_location;
    render::vec3 m_up;
    render::vec3 m_direction;
    render::vec3 m_scale;

};

#endif // TRANSFORM_HPP