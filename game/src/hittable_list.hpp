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

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto& object : objects) {
            if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
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