#pragma once
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "raylib.h"
#include "raymath.h"
#include "transform.hpp"
#include "material.hpp"


class Object {
public:
    Object(const Model& geometry, render::Transform transform={{0, 0, 0,}, {1, 0, 0, 0}, {1, 1, 1}}, render::Material material={{200, 200, 200, 255}, 1.0}) :
        m_model{geometry},
        m_transform{transform},
        m_material{material}
    {
        Image solid = GenImageColor(1, 1, m_material.albedo);
        Texture2D texture = LoadTextureFromImage(solid);
        UnloadImage(solid);
        m_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    }

    void display() const {
        auto obj = transform(m_transform);
        DrawModel(obj, {0, 0, 0}, 1, WHITE);
        DrawModelWires(obj, {0, 0, 0}, 1, LIGHTGRAY);
    }

    /**
     * This method will move a copy of the object by the transform passed in. This is not a particularly
     * efficient way to handle moving objects; it's better to move the rays being cast, but we will need to
     * move the object itself for raylib's 3D drawing.
     * 
     * @param transform: what transform operation to apply to the object (translation, scale, rotation)
     * @return a copy of the object transformed
     */
    Model transform(const render::Transform& transform) const {
        auto obj = m_model;
        obj.transform = MatrixMultiply(
            MatrixMultiply(
                MatrixScale(transform.scale.x, transform.scale.y, transform.scale.z),
                QuaternionToMatrix(transform.rotation)
            ),
            MatrixTranslate(transform.translation.x, transform.translation.y, transform.translation.z));
        return obj;
    }


protected:
    Model m_model;
    render::Transform m_transform;
    render::Material m_material;

};


class Cube : public Object {
public:
    Cube(Vector3 position, Vector3 scale, Quaternion rotation, render::Material material) :
        Object(LoadModelFromMesh(GenMeshCube(scale.x, scale.z, scale.y)), Transform{position, rotation, {1, 1, 1}}, material)
    {

    }


};


class Sphere : public Object {
public:
    Sphere(Vector3 position, Vector3 scale, Quaternion rotation,render::Material material) :
        Object(LoadModelFromMesh(GenMeshSphere(1, 24, 24)), Transform{position, rotation, scale}, material)
    {   
    }

};


class Plane : public Object {
public:
    Plane(Vector3 position, Vector3 scale, Quaternion rotation, render::Material material) :
        Object(LoadModelFromMesh(GenMeshPlane(scale.x, scale.y, 1, 1)), Transform{position, rotation, scale}, material)
    {

    }
};

class Disc : public Object {
public:
    Disc(Vector3 position, Vector3 scale, Quaternion rotation, render::Material material) :
        Object(LoadModelFromMesh(GenMeshPoly(24, 1)), Transform{position, rotation, scale}, material)
    {

    }
};



#endif //OBJECT_HPP