#pragma once
#ifndef CASTER_HPP
#define CASTER_HPP

#include <stdint.h>
#include "raylib.h"
#include "raylib_utilities.hpp"
#include "scene.hpp"
#include "hit_record.hpp"


namespace render {

class Caster {
public:
    Caster(uint8_t bounces, uint8_t scatters) :
        m_bounces{bounces},
        m_scatters{scatters}
    {

    }
    
    virtual bool cast_ray(const Ray& r, double min, double max, HitRecord& rec, const Scene& scene) const = 0;
    
    virtual Vector3 scatter(const Ray& r, const HitRecord& hit_record) const = 0;

private:
    struct metadata {
        bool bounce_again;
        Ray outgoing;
        HitRecord record;
    };

public:
    bool trace_path(const Ray& r, double min, double max, HitRecord& rec, const Scene& scene, uint8_t bounces=0) {
        metadata scatterList[m_scatters];

        // Problem: each hit that scatters requires the scattered rays to be fully computed to move on to the next bounce...
        // This wouldn't be an issue if we were okay with recursive function calls, but I'm not sure it's possible without either
        // calling trace_path recursively, or saving all bounces in memory, then combining them.

        // For now we will allow recusive calls just to get it working and optimize later
        
        // Cast the initial ray which will initialize the hit record(s), and outgoing rays.
        if (!cast_ray(r, min, max, rec, scene)) {
            // This ray points into oblivion, no need to scatter here
            return false;
        }
        
        if (bounces >= m_bounces-1) {
            return true;
        }

        // Initialize the scatter list
        for (uint8_t i=0; i < m_scatters; i++) {
            scatterList[i].bounce_again = true;
            scatterList[i].outgoing = r;
            scatterList[i].record = rec;
        }

        // Scattering in the outer loop so that each bounce's data stays in the cache
        for (uint8_t scatter_i=0; scatter_i < m_scatters; scatter_i++) {
            // Bouncing in the inner loop 
            if (trace_path(scatterList[scatter_i].outgoing, min, max, scatterList[scatter_i].record, scene, bounces+1)) {
                // If the ray cast hits something, bounce
                scatterList[scatter_i].bounce_again = true;
                scatterList[scatter_i].outgoing.position = scatterList[scatter_i].record.hit_point;
                if (bounces == m_bounces-1) {
                    scatterList[scatter_i].outgoing.direction = scatter(scatterList[scatter_i].outgoing, scatterList[scatter_i].record);

                }
                // hit record is already set automatically
            } else {
                // Otherwise, we don't bounce
                scatterList[scatter_i].bounce_again = false;
                break;
            }
        }


        for (uint8_t scatter_i=0; scatter_i < m_scatters; scatter_i++) {
            rec.amplitude += scatterList[scatter_i].record.amplitude;
            rec.albedo += scatterList[scatter_i].record.albedo;
            // We can't actually keep track of multipath this way... this is a problem.
        }



        return true;
    }

private:
    uint8_t m_bounces;
    uint8_t m_scatters;

};

}


#endif // CASTER_HPP