#pragma once
#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include "hittable.hpp"
#include "utilities.hpp"
#include <vector>

namespace render {
namespace hit {

class hittable_list : public hittable {
public:
    hittable_list() :
        objects{}
    {

    }

    hittable_list(std::shared_ptr<hittable> object) :
        hittable_list()
    {
        add(object);
    }

    void clear() { objects.clear(); }
    void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_tmax;

        for (const auto& object : objects) {
            if (object->hit(r, ray_tmin, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
private:
    std::vector<std::shared_ptr<hittable>> objects;
};

}
}

#endif // HITTABLE_LIST_HPP