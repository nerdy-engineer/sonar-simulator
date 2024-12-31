#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "object.hpp"
#include "environment.hpp"


namespace render {

class Scene {
public:
    Scene() : 
        m_objects{},
        m_env{Material{{255, 255, 255, 255}, 1.225, 343}}
    {

    }

    std::vector<Object>& objects() { return m_objects; }
    // I would like a const version of this, but I'm not sure how to acheive it...

    void add(Object obj) { m_objects.push_back(obj); }
    void clear() { m_objects.clear(); }

    const Environment& environment() const { return m_env; }

private:
    std::vector<Object> m_objects;
    
    Environment m_env;

};

}

#endif // SCENE_HPP