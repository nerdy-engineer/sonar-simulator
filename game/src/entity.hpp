#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "transform.hpp"

namespace render {

class Entity {
public:
    Entity(const Transform& transform) : m_transform{transform} {}
    
    vec3 position() const { return m_transform.position(); }
    vec3 up() const { return m_transform.up(); }
    vec3 direction() const { return m_transform.direction(); }
    vec3 scale() const { return m_transform.scale(); }

private:
    Transform m_transform;


};

}

#endif // ENTITY_HPP