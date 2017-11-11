#pragma once

#include <iostream>
#include <cmath>

#include "Vector.h"

namespace veteris
{
    class Normal3
    {
    public:
        float X, Y, Z;
        Normal3(float x, float y, float z)
                : X(x), Y(y), Z(z) {}
        Normal3(const Vector3 &v)
                : X(v.X), Y(v.Y), Z(v.Z) {}
        float operator [] (int i) const
        {
            return (&X)[i];
        }
        float &operator [] (int i)
        {
            return (&X)[i];
        }
        float length_squared() const
        {
            return X*X + Y*Y + Z*Z;
        }
        float length() const
        {
            return sqrtf(length_squared());
        }
        void normalize()
        {
            float inv = 1.F / length();
            X *= inv;
            Y *= inv;
            Z *= inv;
        }
    };
    inline std::ostream &operator << (std::ostream &os, const Normal3 &n)
    {
        os << "[" << n.X << "," << n.Y << "," << n.Z << "]";
        return os;
    }
}