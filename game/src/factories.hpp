#pragma once
#ifndef FACTORIES_HPP
#define FACTORIES_HPP

#include <inc/picojson/picojson.h>
#include <memory>

#include "vec3.hpp"

#include "objects.hpp"
#include "environment.hpp"
#include "scene.hpp"
#include "transform.hpp"
#include "geometry.hpp"


namespace render {

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

vec3 vector_factory(const picojson::value& json) {
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

color3<double> color_factory(const picojson::value& json) {
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


RenderMaterial material_factory(const picojson::value& json) {
    if (json.is<picojson::object>()) {
        auto root = json.get<picojson::object>();
        auto albedo = color_factory(root["albedo"]);
        auto absorbption = root["absorbption"].get<double>();

        return RenderMaterial(albedo, absorbption);
    } else {
        // an invalid json object was passed in
    }
}



Geometry& geometry_factory(const picojson::value& json, RenderMaterial& material) {
    if (json.is<std::string>()) {
        auto type = json.get<std::string>();
        if (type == "sphere") {
            auto r = Sphere{1};
            return r;
        } else if (type == "plane") {
            auto r = Plane{};
            return r;
        } else if (type == "disc") {
            auto r = Disc(1);
            return r;
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
        RenderMaterial material = material_factory(root["material"]);
        Geometry& geometry = geometry_factory(root["geometry"], material);
        Transform transform = transform_factory(root["transform"]);
        // TODO: Object is not yet implemented, need to define what an object is before we can create one.
        return Object(geometry, transform);

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


}

#endif // FACTORIES_HPP