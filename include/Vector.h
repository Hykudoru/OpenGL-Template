#pragma once
#include <math.h>

struct Vec4;

struct Vec2 {
    float x, y;

    Vec2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
};

struct Vec3 {
    float x, y, z;

    static Vec3 zero;

    Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

    virtual float Magnitude() {
        return sqrt(x*x + y*y + z*z);
    }

    Vec3 Normalized() {
        float length = Magnitude();
        Vec3 vec;
        if (length >= 0.00001) {
            vec.x /= length;
            vec.y /= length;
            vec.z /= length;
        }
        return vec;
    }

    static float Dot(const Vec3& a, const Vec3& b) {
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }

    // operator overloading

    // vecA + vecb
    Vec3 operator+(const Vec3& other) {
        return Vec3(this->x + other.x, this->y + other.y, this->z + other.z);
    }

    // vecA - vecb
    Vec3 operator-(const Vec3& other) {
        return Vec3(this->x - other.x, this->y - other.y, this->z - other.z);
    }

    // vecA * scalar
    Vec3 operator*(const float scalar) {
        return Vec3(this->x * scalar, this->y * scalar, this->z * scalar);
    }

    // += -= /= *=
    Vec3& operator+=(const Vec3& other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    Vec3& operator-=(const Vec3& other) {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return *this;
    }
    
    Vec3& operator*=(const float& scalar) {
        this->x *= scalar;
        this->y -= scalar;
        this->z -= scalar;
        return *this;
    }

    Vec3& operator/=(const float& scalar) {
        this->x /= scalar;
        this->y /= scalar;
        this->z /= scalar;
        return *this;
    }
    
    operator Vec2() {
        return Vec2(this->x, this->y);
    }
    
    operator Vec4();
};

Vec3 Vec3::zero(0, 0, 0);


struct Vec4
{
    float x;
    float y;
    float z;
    float w;
    Vec4(float x = 0, float y = 0, float z = 0, float w = 1) : x(x), y(y), z(z), w(w) {}

    static float Dot(const Vec4& a, const Vec4& b) {
        return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
    }
    
    operator Vec3() {
        return Vec3(this->x, this->y, this->z);
    }
};


Vec3::operator Vec4() {
    return Vec4(this->x, this->y, this->z, 1.0f);
}

