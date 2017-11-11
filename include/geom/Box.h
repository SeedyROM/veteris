#pragma once

#include <iostream>
#include <cmath>
#include "Point.h"

inline const float minf(float x, float y) {
    return (x < y) ? x : y;
}
inline const float maxf(float x, float y) {
    return (x > y) ? x : y;
}

namespace veteris
{
    class Box3
    {
    public:
        Point3 min, max;
        Box3() : min(INFINITY, INFINITY, INFINITY), max(-INFINITY, -INFINITY, -INFINITY) {}
        Box3(const Point3 &p) : min(p), max(p) {}
        Box3(const Point3 &MIN, const Point3 &MAX) : min(MIN), max(MAX) {}
        float volume() const
        {
            return (max.X - min.X)*(max.Y - min.Y)*(max.Z - min.Z);
        }
        int longest_side() const
        {
            float dx = max.X - min.X;
            float dy = max.Y - min.Y;
            float dz = max.Z - min.Z;
            return (dx > dy && dx > dz)? 0: (dy > dz)? 1: 2;
        }
        void unionWith(const Point3 &p)
        {
            min.X = minf(min.X, p.X);
            min.Y = minf(min.Y, p.Y);
            min.Z = minf(min.Z, p.Z);
            max.X = maxf(max.X, p.X);
            max.Y = maxf(max.Y, p.Y);
            max.Z = maxf(max.Z, p.Z);
        }
        void unionWith(const Box3 &b)
        {
            min.X = minf(min.X, b.min.X);
            min.Y = minf(min.Y, b.min.Y);
            min.Z = minf(min.Z, b.min.Z);
            max.X = maxf(max.X, b.max.X);
            max.Y = maxf(max.Y, b.max.Y);
            max.Z = maxf(max.Z, b.max.Z);
        }
        bool overlaps(const Box3 &b) const
        {
            return (max.X >= b.min.X) && (min.X <= b.max.Y)
                   && (max.Y >= b.min.Y) && (min.Y <= b.max.Y)
                   && (max.Z >= b.min.Z) && (min.Z <= b.max.Z);
        }
        bool contains(const Point3 &p) const
        {
            return (p.X >= min.X) && (p.X <= max.X)
                   && (p.Y >= min.Y) && (p.Y <= max.Y)
                   && (p.Z >= min.Z) && (p.Z <= max.Z);
        }


    };
    inline std::ostream &operator << (std::ostream &os, const Box3 &b)
    {
        os << "min: " << b.min << "\n";
        os << "max: " << b.max;
        return os;
    }
}