#pragma once
#ifndef FACTORIES_HPP
#define FACTORIES_HPP

#include <inc/picojson/picojson.h>
#include <fstream>
#include <memory>

#include "vec3.hpp"

#include "objects.hpp"
#include "environment.hpp"
#include "scene.hpp"
#include "transform.hpp"
#include "geometry.hpp"


Scene scene_factory(const std::string& json_filepath){
    std::string jsonString = "";
    std::ifstream jsonFile(json_filepath, std::ios_base::in);
    jsonFile.read(&jsonString[0], jsonFile.tellg());
    picojson::value json;
    picojson::parse(json, jsonString);
    auto root = json.get<picojson::object>();
    return {environment_factory(root["environment"]), objects_factory(root["objects"])};
}

Environment environment_factory(const picojson::value& json) {
    if (json.is<picojson::object>()) {
        auto root = json.get<picojson::object>();
        auto sos = root["speed of sound"];
        auto density = root["density"];
        if (!root["speed of sound"].is<double>()) {
            // Throw and error here
        }
        if (!root["density"].is<double>()) {
            // And here
        }
        return Environment(sos.get<double>(), density.get<double>());
    } else {
        // an invalid json object was passed in
    }
}

render::vec3 vector_factory(const picojson::value& json) {
    if (json.is<picojson::array>()) {
        // It should be an length 3 array of doubles, so let's make sure
        auto root = json.get<picojson::array>();
        if (root.size() != 3) {
            // Vectors in 3d space must have 3 components
        }
        std::vector<double> values{3};
        for (const auto& val : root) {
            if (!val.is<double>()) {
                // Vectors in 3d space must be numeric
            }
            values.push_back(val.get<double>());
        }
        return {values[0], values[1], values[2]};
    } else {
        // an invalid json object was passed in
    }
}

render::color3<double> color_factory(const picojson::value& json) {
    if (json.is<picojson::array>()) {
        // It should be an length 3 array of doubles, so let's make sure
        auto root = json.get<picojson::array>();
        if (root.size() != 3) {
            // Vectors in 3d space must have 3 components
        }
        std::vector<double> values{3};
        for (const auto& val : root) {
            if (!val.is<double>()) {
                // Vectors in 3d space must be numeric
            }
            values.push_back(val.get<double>());
        }
        return {values[0], values[1], values[2]};
    } else {
        // an invalid json object was passed in
    }
}


Transform transform_factory(const picojson::value& json) {
    if (json.is<picojson::object>()) {
        auto root = json.get<picojson::object>();
        auto position = vector_factory(root["position"]);
        auto orientation_up = vector_factory(root["orientation"].get<picojson::object>()["up"]);
        auto orientation_direction = vector_factory(root["orientation"].get<picojson::object>()["direction"]);
        auto scale = vector_factory(root["scale"]);
        return {position, orientation_up, orientation_direction, scale};
    } else {
        // an invalid json object was passed in
    }
}


Material material_factory(const picojson::value& json) {
    if (json.is<picojson::object>()) {
        auto root = json.get<picojson::object>();
        auto albedo = color_factory(root["albedo"]);
        auto absorbption = root["absorbption"].get<double>();

        return Material(albedo, absorbption);
    } else {
        // an invalid json object was passed in
    }
}



std::shared_ptr<Geometry> geometry_factory(const picojson::value& json) {
    if (json.is<std::string>()) {
        auto type = json.get<std::string>();
        if (type == "sphere") {
            return std::make_shared<Geometry>(Sphere(0.5));
        } else if (type == "plane") {
            return std::make_shared<Geometry>(Plane());
        } else if (type == "disc") {
            return std::make_shared<Geometry>(Disc(0.5));
        } else {
            // Bad geometry type
        }
        
    } else if (json.is<picojson::object>()) {
        // This will get used for mesh object interpreters where the path will be used to load an object
    } else {
        // an invalid json object was passed in
    }
}


Object object_factory(const picojson::value& json) {
    if (json.is<picojson::object>()) {
        auto root = json.get<picojson::object>();
        std::shared_ptr<Geometry> geometry = geometry_factory(root["geometry"]);
        Transform transform = transform_factory(root["transform"]);
        Material material = material_factory(root["material"]);
        // TODO: Object is not yet implemented, need to define what an object is before we can create one.

        return Object(geometry, transform, material);

    } else {
        // an invalid json object was passed in
    }
}

std::vector<std::shared_ptr<Object>> objects_factory(const picojson::value& json) {
    if (json.is<picojson::array>()) {
        auto root = json.get<picojson::array>();
        std::vector<std::shared_ptr<Object>> objs{root.size()};
        for( const auto& obj : root) {
            objs.push_back(std::make_shared<Object>(object_factory(obj)));
        }
        return objs;
    } else {
        // an invalid json object was passed in
    }
}



#endif // FACTORIES_HPP