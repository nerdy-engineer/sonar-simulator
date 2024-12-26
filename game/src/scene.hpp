#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP


#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <inc/picojson/picojson.h>
#include "factories.hpp"
#include "objects.hpp"
#include "environment.hpp"

namespace render {
class Scene {
public:
    Scene() :
        m_environment{},
        m_objects{}
    {

    }
    Scene(const Environment& environment, const std::vector<std::shared_ptr<Object>>& objects):
        m_environment{environment},
        m_objects{objects}
    {
        
    }

    void add_object(Object& new_object) { m_objects.push_back(std::make_shared<Object>(new_object)); }

    std::vector<std::shared_ptr<Object>> objects() { return m_objects; }

    const Environment& environment() const { return m_environment; }

    inline const HittableList& hittable_world() const {
        HittableList geometries;
        for (const auto object : m_objects) {
            geometries.add(object->geometry());
        }
    }

private:
    Environment m_environment;
    std::vector<std::shared_ptr<Object>> m_objects;



};


Scene scene_factory(const std::string& json_filepath){
    std::string jsonString = "";
    std::ifstream jsonFile(json_filepath, std::ios_base::in);
    jsonFile.read(&jsonString[0], jsonFile.tellg());
    picojson::value json;
    picojson::parse(json, jsonString);
    auto root = json.get<picojson::object>();
    return {environment_factory(root["environment"]), objects_factory(root["objects"])};
}

}


#endif