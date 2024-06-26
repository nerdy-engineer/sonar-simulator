#pragma once
#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"
#include "interval.hpp"
#include <limits>


namespace render {

template <typename T>
struct color4 {
    T r;
    T g;
    T b;
    T a;
};

template <typename T>
struct color3 {
    T r;
    T g;
    T b;
};

template <typename T>
color3<T> operator*(vec3 first, color3<T> c) {
    return {first.x * c.r, first.y * c.g, first.z * c.b };
}

template <typename T>
color3<T> operator*(color3<T> c, vec3 second) {
    return second*c;
}

template <typename T>
color3<T> operator*(color3<T> c1, color3<T> c2) {
    return {c1.r+c2.r, c1.g+c2.g, c1.b+c2.b};
}

template <typename A, typename T>
color3<T> operator*(A first, color3<T> c) {
    return {first*c.r, first*c.g, first*c.b};
}

template <typename A, typename T>
color3<T> operator*(color3<T> c, A first) {
    return first*c;
}


template <typename A, typename T>
color4<T> operator*(A first, color4<T> c) {
    return {first*c.r, first*c.g, first*c.b, first*c.a};
}

template <typename A, typename T>
color4<T> operator*(color4<T> c, A first) {
    return first*c;
}


template <typename T>
color3<T> operator/(color3<T> a, double divisor) {
    return {a.r/divisor, a.g/divisor, a.b/divisor};
}

template <typename T>
color4<T> operator/(color4<T> a, double divisor) {
    return {a.r/divisor, a.g/divisor, a.b/divisor, a.a/divisor};
}

template <typename T>
color3<T> operator+(color3<T> a, color3<T> b) {
    return {a.r + b.r, a.g + b.g, a.b + b.b};
}

template <typename T>
color3<T>& operator+=(color3<T>& lhs, const color3<T>& rhs) {
    lhs.r += rhs.r;
    lhs.g += rhs.g;
    lhs.b += rhs.b;    
    return lhs;
}

template <typename T>
color4<T> operator+(color4<T> a, color4<T> b) {
    return {a.r + b.r, a.g + b.g, a.b + b.b, a.a + b.a};
}

template <typename T>
color4<T>& operator+=(color4<T>& lhs, const color4<T>& rhs) {
    lhs.r += rhs.r;
    lhs.g += rhs.g;
    lhs.b += rhs.b; 
    lhs.a += rhs.a;
    return lhs;
}

template <typename T>
color3<T> operator+(vec3 a, color3<T> b) {
    return {a.x() + b.r, a.y() + b.g, a.z() + b.b};
}

template <typename T>
color3<T> operator+(color3<T> b, vec3 a) {
    return {a.x() + b.r, a.y() + b.g, a.z() + b.b};
}

color4<double> promote(color3<double> a) {
    return {a.r, a.g, a.b, 1.0};
}

template <typename T>
color4<T> promote(color3<T> a) {
    return {a.r, a.g, a.b, std::numeric_limits<T>::max()};
}

template <typename T>
color3<uint8_t> quantize(color3<T> c) {
    return {uint8_t(255.9999*c.r), uint8_t(255.9999*c.g), uint8_t(255.9999*c.b)};
}

template <typename T>
color4<uint8_t> quantize(color4<T> c) {
    return {uint8_t(255.9999*c.r), uint8_t(255.9999*c.g), uint8_t(255.9999*c.b), uint8_t(255.9999*c.a)};
}


}

#endif