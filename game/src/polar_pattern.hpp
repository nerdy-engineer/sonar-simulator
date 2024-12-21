#pragma once
#ifndef POLAR_PATTERN
#define POLAR_PATTERN

#include <math.h>
#include "vec3.hpp"

class PolarPattern {
public:
    virtual ~PolarPattern() = default;
    virtual double coefficient(double phi, double theta) const = 0;
    virtual double coefficient(const render::vec3& direction) const = 0;

};


class SimpleCardioid : public PolarPattern {
public:
    SimpleCardioid(double alpha) :
        m_alpha{alpha}
    {

    }

    double coefficient(double phi, double theta) const override {
        auto costheta = cos(theta);
        auto sintheta = sin(theta);
        auto sinphi =  sin(phi);
        auto cosphi = cos(phi);
        render::vec3 direction = {costheta * sinphi,  cosphi, sintheta*sinphi};
        return coefficient(direction);
    }

    double coefficient(const render::vec3& direction) const override {
        double cos_angle = dot(direction, {0, 0, 1});
        return m_alpha * cos_angle;
    }

private:
    double m_alpha;

};



#endif // POLAR_PATTERN