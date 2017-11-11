#pragma once

#include <iostream>
#include <cmath>

#include "Base.h"

namespace veteris {
    struct Vector3 : public BaseVector3 {
        using BaseVector3::BaseVector3;

        Vector3 &operator *= (float f) {
            x *= f;
            y *= f;
            z *= f;
            return *this;
        }
        float length2() const {
            return x*x + y*y + z*z;
        }
        float length() const {
            return sqrtf(length2());
        }
        void normalize() {
            *this *= 1.F/length();
        }
    };
}

//    struct Point3;
//    struct Normal3;
//    struct Vector3
//    {
//        float x, y, z;
//        Vector3(float x, float y, float z)
//                : x(x), y(y), z(z) {}
//        Vector3(const Vector3 &v)
//                : x(v.x), y(v.y), z(v.z) {}
//        float &operator [] (int i) {
//            return (&x)[i];
//        }
//        float operator [] (int i) const {
//            return (&x)[i];
//        }
//        float length2() const {
//            return x*x + y*y + z*z;
//        }
//        float length() const {
//            return sqrtf(length2());
//        }
//        void normalize() {
//            *this *= 1.F/length();
//        }
//        Vector3 operator - () const {
//            return Vector3(-x, -y, -z);
//        }
//        Vector3 operator + (const Vector3 &v) const {
//            return Vector3(x+v.x, y+v.y, z+v.z);
//        }
//        Vector3 &operator += (const Vector3 &v) {
//            x += v.x;
//            y += v.y;
//            z += v.z;
//            return *this;
//        }
//        Vector3 operator - (const Vector3 &v) const {
//            return Vector3(x-v.x, y-v.y, z-v.z);
//        }
//        Vector3 &operator -= (const Vector3 &v) {
//            x -= v.x;
//            y -= v.y;
//            z -= v.z;
//            return *this;
//        }
//        Vector3 operator * (float f) const {
//            return Vector3(x*f, y*f, z*f);
//        }
//        Vector3 &operator *= (float f) {
//            x *= f;
//            y *= f;
//            z *= f;
//            return *this;
//        }
//        Vector3 operator / (float f) const {
//            float inv = 1.F / f;
//            return Vector3(x*inv, y*inv, z*inv);
//        }
//        Vector3 &operator /= (float f) {
//            float inv = 1.F / f;
//            x *= inv;
//            y *= inv;
//            z *= inv;
//            return *this;
//        }
//    };
//    inline Vector3 operator * (float f, const Vector3 &v) {
//        return Vector3(f*v.x, f*v.y, f*v.z);
//    }
//    inline std::ostream &operator << (std::ostream &os, const Vector3 &v) {
//        os << "[" << v.x << "," << v.y << "," << v.z << "]";
//        return os;
//    }