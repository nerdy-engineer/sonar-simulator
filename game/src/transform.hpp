#pragma once
#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "vec3.hpp"

namespace render {
class Transform {
public:
    Transform(const vec3& location,
              const vec3& up,
              const vec3& direction,
              const vec3& scale) :
        m_location{location},
        m_up{up},
        m_direction{direction},
        m_scale{scale}
    {

    }

    vec3 position() const { return m_location; }
    vec3 up() const { return m_up; }
    vec3 direction() const { return m_direction; }
    vec3 scale() const { return m_scale; }

private:
    vec3 m_location;
    vec3 m_up;
    vec3 m_direction;
    vec3 m_scale;

};

}

#endif // TRANSFORM_HPP