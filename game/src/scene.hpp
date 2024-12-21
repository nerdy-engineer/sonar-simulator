#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP


#include <string>
#include <vector>
#include <memory>
#include "factories.hpp"
#include "objects.hpp"
#include "environment.hpp"


class Scene {
public:
    Scene(const Environment& environment, const std::vector<std::shared_ptr<Object>>& objects):
        m_environment{environment},
        m_objects{objects}
    {
        
    }


private:
    Environment m_environment;
    std::vector<std::shared_ptr<Object>> m_objects;



};




#endif