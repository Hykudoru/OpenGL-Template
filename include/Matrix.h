#pragma once
#include <Vector.h>
#include <math.h>
class Matrix3x3;
class Matrix4x4;

class Matrix3x3 {
public:
    float m[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
    };

    inline static float identity[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
    };

    static Matrix3x3 RotZ(float theta) {
       float C = cos(theta);
       float S = sin(theta);
       Matrix3x3 rot = {{
        {C, -S, 0},
        {S, C, 0},
        {0, 0, 1},
       }};

       return rot;
    }

    static Matrix3x3 RotY(float theta) {
       float C = cos(theta);
       float S = sin(theta);
       Matrix3x3 rot = {{
        {C, 0, S},
        {0, 1, 0},
        {-S, 0, C},
       }};

       return rot;
    }

    static Matrix3x3 RotX(float theta) {
       float C = cos(theta);
       float S = sin(theta);
       Matrix3x3 rot = {{
        {1, 0, 0},
        {0, C, -S},
        {0, S, C},
       }};

       return rot;
    }

    static Matrix3x3 Multiply(const Matrix3x3& A, const Matrix3x3& B) {
        Matrix3x3 result3x3;
        for (size_t r = 0; r < 3; r++) {
            Vec3 rowVec(A.m[r][0], A.m[r][1], A.m[r][2]);
            for (size_t c = 0; c < 3; c++) {
                Vec3 colVec(B.m[0][c], B.m[1][c], B.m[2][c]);
                result3x3.m[r][c] = Vec3::Dot(rowVec, colVec);
            }
        }
        return result3x3;
    }

    

    static Matrix3x3 Transposed(const Matrix3x3& matrix) {
        Matrix3x3 result3x3;
            for (size_t r = 0; r < 3; r++) {
                for (size_t c = 0; c < 3; c++) {
                    result3x3.m[r][c] = matrix.m[c][r];
                }
            }
        return result3x3;
    }
};

class Matrix4x4 {
public:
    float m[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    };
};

// A * B
Matrix3x3 operator*(const Matrix3x3& A, const Matrix3x3& B) {
    return Matrix3x3::Multiply(A, B);
}