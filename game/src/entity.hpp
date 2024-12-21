#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "transform.hpp"


class Entity {
public:
    Entity(const Transform& transform) : m_transform{transform} {}

private:
    Transform m_transform;


};



#endif // ENTITY_HPP