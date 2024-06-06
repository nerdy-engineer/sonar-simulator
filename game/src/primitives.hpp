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

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
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

        return true;
    }


private:
    point3 m_center;
    double m_radius;

};

}
}

#endif // PRIMITIVES_HPP