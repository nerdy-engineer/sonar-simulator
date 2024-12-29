#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "object.hpp"


namespace render {

class Scene {
public:
    Scene() : 
        m_objects{}
    {

    }

    std::vector<Object> objects() { return m_objects; }
    void add(Object obj) { m_objects.push_back(obj); }
    void clear() { m_objects.clear(); }

private:
    std::vector<Object> m_objects;


};

}

#endif // SCENE_HPP