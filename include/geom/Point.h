#pragma once

#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

namespace veteris {
    class Point3
    {
    public:
        float X, Y, Z;
        Point3() : X(0.F), Y(0.F), Z(0.F) {}
        Point3(float x, float y, float z) : X(x), Y(y), Z(z) {}
        Point3(const Point3 &p) : X(p.X), Y(p.Y), Z(p.Z) {}
        float operator [] (int i) const
        {
            return (&X)[i];
        }
        float &operator [] (int i)
        {
            return (&X)[i];
        }
        float distance_squared(const Point3 &p) const
        {
            float tx = X - p.X;
            float ty = Y - p.Y;
            float tz = Z - p.Z;
            return tx*tx + ty*ty + tz*tz;
        }
        float distance(const Point3 &p) const
        {
            return sqrtf(distance_squared(p));
        }
        sf::Vector2f asVector2f(float cx, float cy) {
            return sf::Vector2f(X + cx, Y + cy);
        }
    };
    inline std::ostream &operator << (std::ostream &os, const Point3 &p)
    {
        os << "[" << p.X << "," << p.Y << "," << p.Z << "]";
        return os;
    }
}