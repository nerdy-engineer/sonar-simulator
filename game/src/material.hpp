#pragma once
#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"


class RenderMaterial {
public:
    RenderMaterial(const render::color3<double>& albedo, double absorbption) :
        m_albedo{albedo},
        m_absorbption{absorbption}
    {

    }

    render::color3<double> albedo() const { return m_albedo; }
    double absorbption() const { return m_absorbption; }

private:
    render::color3<double> m_albedo;
    double m_absorbption;


};

#endif // MATERIAL_HPP