#pragma once
#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <memory>
#include "entity.hpp"
#include "transform.hpp"
#include "geometry.hpp"
#include "material.hpp"

namespace render {

class Object : public Entity {
public:
    Object(Geometry& geometry, Transform transform) :
        Entity(transform),
        m_geometry{std::make_shared<Geometry>(geometry)}
    {

    }

    GeometryType shape() const { return m_geometry->shape(); }
    std::shared_ptr<const Geometry> geometry() const { return m_geometry; }
    // RenderMaterial material() const { return m_material; }

private:

    std::shared_ptr<Geometry> m_geometry;


};

}

#endif // OBJECTS_HPP