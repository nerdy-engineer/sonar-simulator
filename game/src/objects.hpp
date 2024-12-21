#pragma once
#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <memory>
#include "entity.hpp"
#include "transform.hpp"
#include "geometry.hpp"


class Object : public Entity {
public:
    Object(std::shared_ptr<Geometry> geometry, Transform transform, const Material& material) :
        Entity(transform),
        m_geometry{geometry},
        m_material{material}
    {

    }


private:
    std::shared_ptr<Geometry> m_geometry;
    Material m_material;


};


#endif // OBJECTS_HPP