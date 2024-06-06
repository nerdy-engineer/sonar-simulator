#pragma once
#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include "utilities.hpp"

namespace render {

class interval {
public:
    double min, max;
    interval() : min(+infinity), max(-infinity) {}  // Default interval is empty
    interval(double min, double max) :
        min(min),
        max(max)
    {

    }

    double size() const {
        return max - min;
    }

    bool contains(double x) const {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const {
        return min < x && x < max;
    }

    static const interval emtpy, universe;

};

const interval interval::emtpy = interval(+infinity, -infinity);
const interval interval::universe = interval (-infinity, +infinity);

}

#endif // INTERVAL_HPP