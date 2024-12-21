#pragma once
#ifndef ILLUMINATOR_HPP
#define ILLUMINATOR_HPP

#include "vec3.hpp"
#include "entity.hpp"
#include "geometry.hpp"
#include "transform.hpp"
#include "polar_pattern.hpp"


class Illuminator : Entity {
public:
    Illuminator(std::shared_ptr<Geometry> geometry, const Transform& transform, std::shared_ptr<PolarPattern> radiation_pattern, double intensity) :
        Entity(transform),
        m_geometry{geometry},
        m_radiation_pattern{radiation_pattern},
        m_intensity{intensity}
    {

    }

    void intensity(double intensity) { m_intensity = intensity; }
    double intensity() { return m_intensity; }
    /**
     * Gets the intensity due to combined radiation pattern and intensity
     * Flip vector switches between assuming rays are hitting the geometry (default; true) and
     * being cast from the geometry (false)
     * 
     */
    double effective_intensity(const render::vec3& direction, bool flip_vector=true) const {
        return m_intensity * m_radiation_pattern->coefficient(direction);
    }

    void radiation_pattern(std::shared_ptr<PolarPattern> radiation_pattern) { m_radiation_pattern = radiation_pattern; }
    
    void geometry(std::shared_ptr<Geometry> geometry) { m_geometry = geometry; }

private:
    std::shared_ptr<Geometry> m_geometry;
    std::shared_ptr<PolarPattern> m_radiation_pattern;
    double m_intensity;

};


#endif // ILLUMINTOR_HPP