#pragma once
#ifndef WORLD_HPP
#define WORLD_HPP

#include "hittable.hpp"
#include "hittable_list.hpp"
#include "utilities.hpp"

class world {
public:
    world(double speed_of_sound=343.0):
        m_hitlist{},
        m_speed_of_sound{speed_of_sound}
    {
        
    }

    void speed_of_sound(double speed_of_sound) { m_speed_of_sound = speed_of_sound; }
    double speed_of_sound() const noexcept { return m_speed_of_sound; }

    size_t pulse_periods() { return m_pulse_periods; }
    void pulse_periods(size_t periods) { m_pulse_periods = periods; }

    double pulse_frequency() { return m_pulse_frequency; }
    void pulse_frequency(size_t frequency) { m_pulse_frequency = frequency; }

    size_t pulse_samples(double sample_rate) { return m_pulse_periods * sample_rate / m_pulse_frequency; }

    inline void clear() { m_hitlist.clear(); }
    inline void add(std::shared_ptr<render::hittable> object) { m_hitlist.add(object); }
    inline const render::hit::hittable_list& hittable_world() const { return m_hitlist; }



private:
    render::hit::hittable_list m_hitlist;
    double m_speed_of_sound;
    size_t m_pulse_periods;
    double m_pulse_frequency;


};



#endif // WORLD_HPP