#pragma once
#include "Vector.h"
#include "Matrix.h"

class Transform 
{
public:
    Vec3 position;
    Matrix3x3 rotation;
    float scale = 1.0f;

    Transform(const Vec3& pos, float _scale) : position(pos),  scale(_scale) {

    }

    Matrix4x4 TRS() {
        Matrix4x4 model = {{
                {scale * rotation.m[0][0], rotation.m[0][1], rotation.m[0][2], position.x},
                {rotation.m[1][0], scale * rotation.m[1][1], rotation.m[1][2], position.y},
                {rotation.m[2][0], rotation.m[2][1], scale * rotation.m[2][2], position.z},
                {0, 0, 0, 1},
            }};

        return model;
    }
};