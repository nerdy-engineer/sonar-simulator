#pragma once
#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "utilities.hpp"
#include "hit_record.hpp"
#include "material.hpp"
#include "environment.hpp"


namespace render {

enum class GeometryType {
    SPHERE,
    DISC,
    PLANE,
    LIST
};

class Geometry {
public:
    Geometry(GeometryType shape) : m_shape{shape} {}
    virtual ~Geometry() = default;
    virtual bool hit(const render::ray& r, render::interval ray_t, render::hit_record& rec, const Environment& env) const = 0;
    GeometryType shape() const { return m_shape; }
protected:
    GeometryType m_shape;
    Material m_material;

};

class HittableList : Geometry {
public:
    HittableList(std::vector<std::shared_ptr<const Geometry>> hit_list = {}) :
        Geometry(GeometryType::LIST),
        m_geometries{hit_list}
    {

    }

    void clear() { m_geometries.clear(); }
    void add(std::shared_ptr<Geometry> object) { m_geometries.push_back(object); }
    void add(std::shared_ptr<const Geometry> object) { m_geometries.push_back(object); }

    bool hit(const render::ray& r, render::interval ray_t, render::hit_record& rec, const Environment& env) const override {
        render::hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto& object : m_geometries) {
            if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec, env)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }

private:
    std::vector<std::shared_ptr<const Geometry>> m_geometries;



};

class Sphere : public Geometry {
public:
    Sphere(double radius) :
        Geometry(GeometryType::SPHERE),
        m_radius{radius}
    {
        
    }

    bool hit(const render::ray& r, render::interval ray_t, render::hit_record& rec, const Environment& env) const override {
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
        rec.color *= render::promote(m_material.albedo());
        rec.amplitude *= m_material.absorbption();
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
        Geometry(GeometryType::DISC),
        m_radius{radius}
    {

    }

    bool hit(const render::ray& r, render::interval ray_t, render::hit_record& rec, const Environment& env) const override {
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
            rec.color *= render::promote(m_material.albedo());
            rec.amplitude *= m_material.absorbption();
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
    Plane() : 
        Geometry(GeometryType::PLANE)
    {}

    bool hit(const render::ray& r, render::interval ray_t, render::hit_record& rec, const Environment& env) const override {
        double ray_normal_dot = dot(r.direction(), {0, 0, 1});
        double t = dot(-r.origin(), {0, 0, 1}) / ray_normal_dot;
        if (t < 0) { return false; }
        render::vec3 p = r.at(t);

        rec.t = t;
        rec.p = p;
        rec.set_face_normal(r, {0, 0, 1});
        rec.distance_traveled += t;
        rec.color *= render::promote(m_material.albedo());
        rec.amplitude *= material.absorbption();
        rec.f_factor *= 1.0;

        // auto vel = dot(r, motion_vector);
        // rec.f_factor *= sos/(sos+vel);

        return true;
    }


};



}

#endif // GEOMETRY_HPP
