#pragma once
#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

class Environment {
public:
    Environment(double speed_of_sound=343.0, double medium_density=1.225) :
        m_speed_of_sound{speed_of_sound},
        m_density{medium_density}
    {
        
    }

    double acoustic_impedance() const { return m_density * m_speed_of_sound; }
    double speed_of_sound() const { return m_speed_of_sound; }
    double medium_density() const { return m_density; }


private:
    double m_speed_of_sound;
    double m_density;


};


#endif // ENVIRONMENT_HPP