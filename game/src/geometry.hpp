#pragma once
#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "utilities.hpp"
#include "hit_record.hpp"
#include "material.hpp"
#include "environment.hpp"

class Geometry {
public:
    virtual ~Geometry() = default;
    virtual bool hit(const render::ray& r, render::interval ray_t, render::hit_record& rec, const Material& material, const Environment& env) const = 0;

protected:


};



class Sphere : public Geometry {
public:
    Sphere(double radius) :
        m_radius{radius}
    {
        
    }

    bool hit(const render::ray& r, render::interval ray_t, render::hit_record& rec, const Material& material, const Environment& env) const override {
        render::vec3 oc = -r.origin();  // Assuming zero centered, the object containing the geometry will handle transforming positions, rotations, and scale
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
        render::vec3 outward_normal = rec.p / m_radius; //Normally (rec.p - m_center) / m_radius but we get to assume a zero center because the object will do the transformations.
        rec.set_face_normal(r, outward_normal);
        rec.distance_traveled += root;
        rec.color *= render::promote(material.albedo());
        rec.amplitude *= material.absorbption();
        rec.f_factor *= 1.0; // 1.0 For stationary targets
        
        // auto vel = dot(r, motion_vector);
        // rec.f_factor *= sos/(sos+vel);

        return true;
    }
private:
    double m_radius;


};


class Disc : public Geometry {
public:
    Disc(double radius) :
        m_radius{radius}
    {

    }

    bool hit(const render::ray& r, render::interval ray_t, render::hit_record& rec, const Material& material, const Environment& env) const override {
        double ray_normal_dot = dot(r.direction(), {0, 0, 1});
        double t = dot(-r.origin(), {0, 0, 1}) / ray_normal_dot;
        if (t < 0) { return false; }
        render::vec3 p = r.at(t);
        double radius = p.length();

        if (radius <= m_radius) {
            // Disc hit, fill out the hit record
            rec.t = t;
            rec.p = p;
            rec.set_face_normal(r, {0, 0, 1});
            rec.distance_traveled += t;
            rec.color *= render::promote(material.albedo());
            rec.amplitude *= material.absorbption();
            rec.f_factor *= 1.0; // 1.0 for stationary targets

            // auto vel = dot(r, motion_vector);
            // rec.f_factor *= sos/(sos+vel);

            return true;
        }

        return false;
    }


private:
    double m_radius;
};

class Plane : public Geometry {
public:
    Plane() {}

    bool hit(const render::ray& r, render::interval ray_t, render::hit_record& rec, const Material& material, const Environment& env) const override {
        double ray_normal_dot = dot(r.direction(), {0, 0, 1});
        double t = dot(-r.origin(), {0, 0, 1}) / ray_normal_dot;
        if (t < 0) { return false; }
        render::vec3 p = r.at(t);

        rec.t = t;
        rec.p = p;
        rec.set_face_normal(r, {0, 0, 1});
        rec.distance_traveled += t;
        rec.color *= render::promote(material.albedo());
        rec.amplitude *= material.absorbption();
        rec.f_factor *= 1.0;

        // auto vel = dot(r, motion_vector);
        // rec.f_factor *= sos/(sos+vel);

        return true;
    }


};


#endif // GEOMETRY_HPP
