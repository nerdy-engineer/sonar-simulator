#pragma once
#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include "utilities.hpp"
#include "hittable.hpp"

namespace render {
namespace primitives {


class sphere : public hittable {
public:
    sphere(const point3& center, double radius) :
        m_center{center},
        m_radius{radius}
    {

    }

    bool hit(const ray& r, interval ray_t, hit_record& rec, double sos) const override {
        vec3 oc = m_center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - m_radius * m_radius;
        
        auto discriminant = h*h - a*c;
        if (discriminant < 0) 
            return false;

        auto sqrtd = sqrt(discriminant);
        auto root = (h - sqrtd) / a;

        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root)) {
                return false;
            }
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - m_center) / m_radius;
        rec.set_face_normal(r, outward_normal);
        rec.distance_traveled += root;
        rec.color *= promote(m_color);
        rec.amplitude *= m_absorbtion;
        rec.f_factor *= 1.0; // 1.0 For stationary targets
        
        // auto vel = dot(r, motion_vector);
        // rec.f_factor *= sos/(sos+vel);


        return true;
    }


private:
    point3 m_center;
    double m_radius;
    color3<double> m_color;
    double m_absorbtion;

};

}
}

#endif // PRIMITIVES_HPP