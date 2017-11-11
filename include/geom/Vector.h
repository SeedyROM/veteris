#pragma once

#include <iostream>
#include <cmath>

namespace veteris
{
    class Point3;
    class Normal3;
    class Vector3
    {
    public:
        float X, Y, Z;
        Vector3(float x, float y, float z)
                : X(x), Y(y), Z(z) {}
        Vector3(const Vector3 &v)
                : X(v.X), Y(v.Y), Z(v.Z) {}
//        Vector3(const Point3 &from, const Point3 &to)
//                : X(to.X - from.X), Y(to.Y - from.Y), Z(to.Z - from.Z) {}
//        Vector3(const Normal3 &n)
//                : X(n.X), Y(n.Y), Z(n.Z) {}
        float &operator [] (int i)
        {
            return (&X)[i];
        }
        float operator [] (int i) const
        {
            return (&X)[i];
        }
        float length2() const
        {
            return X*X + Y*Y + Z*Z;
        }
        float length() const
        {
            return sqrtf(length2());
        }
        void normalize()
        {
            *this *= 1.F/length();
        }
        Vector3 operator - () const
        {
            return Vector3(-X, -Y, -Z);
        }
        Vector3 operator + (const Vector3 &v) const
        {
            return Vector3(X+v.X, Y+v.Y, Z+v.Z);
        }
        Vector3 &operator += (const Vector3 &v)
        {
            X += v.X;
            Y += v.Y;
            Z += v.Z;
            return *this;
        }
        Vector3 operator - (const Vector3 &v) const
        {
            return Vector3(X-v.X, Y-v.Y, Z-v.Z);
        }
        Vector3 &operator -= (const Vector3 &v)
        {
            X -= v.X;
            Y -= v.Y;
            Z -= v.Z;
            return *this;
        }
        Vector3 operator * (float f) const
        {
            return Vector3(X*f, Y*f, Z*f);
        }
        Vector3 &operator *= (float f)
        {
            X *= f;
            Y *= f;
            Z *= f;
            return *this;
        }
        Vector3 operator / (float f) const
        {
            float inv = 1.F / f;
            return Vector3(X*inv, Y*inv, Z*inv);
        }
        Vector3 &operator /= (float f)
        {
            float inv = 1.F / f;
            X *= inv;
            Y *= inv;
            Z *= inv;
            return *this;
        }
    };
    inline Vector3 operator * (float f, const Vector3 &v)
    {
        return Vector3(f*v.X, f*v.Y, f*v.Z);
    }
    inline std::ostream &operator << (std::ostream &os, const Vector3 &v)
    {
        os << "[" << v.X << "," << v.Y << "," << v.Z << "]";
        return os;
    }
}