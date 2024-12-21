#pragma once
#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "utilities.hpp"
#include "hit_record.hpp"

namespace render {

class hittable {
public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec, double sos) const = 0;
};


}

#endif // HITTABLE_HPP