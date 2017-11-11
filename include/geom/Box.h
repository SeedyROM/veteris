#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>
#include "Point.h"

namespace veteris {
    class Box3 {
    public:
        Point3 min, max;
        Box3() : min(INFINITY, INFINITY, INFINITY), max(-INFINITY, -INFINITY, -INFINITY) {}
        Box3(const Point3 &p) : min(p), max(p) {}
        Box3(const Point3 &MIN, const Point3 &MAX) : min(MIN), max(MAX) {}
        float volume() const {
            return (max.x - min.x)*(max.y - min.y)*(max.z - min.z);
        }
        int longest_side() const {
            float dx = max.x - min.x;
            float dy = max.y - min.y;
            float dz = max.z - min.z;
            return (dx > dy && dx > dz)? 0: (dy > dz)? 1: 2;
        }
        void union_with(const Point3 &p) {
            min.x = std::min(min.x, p.x);
            min.y = std::min(min.y, p.y);
            min.z = std::min(min.z, p.z);
            max.x = std::max(max.x, p.x);
            max.y = std::max(max.y, p.y);
            max.z = std::max(max.z, p.z);

        }
        void union_with(const Box3 &b) {
            min.x = std::min(min.x, b.min.x);
            min.y = std::min(min.y, b.min.y);
            min.z = std::min(min.z, b.min.z);
            max.x = std::max(max.x, b.max.x);
            max.y = std::max(max.y, b.max.y);
            max.z = std::max(max.z, b.max.z);
        }
        bool overlaps(const Box3 &b) const {
            return (max.x >= b.min.x) && (min.x <= b.max.y)
                   && (max.y >= b.min.y) && (min.y <= b.max.y)
                   && (max.z >= b.min.z) && (min.z <= b.max.z);
        }
        bool contains(const Point3 &p) const {
            return (p.x >= min.x) && (p.x <= max.x)
                   && (p.y >= min.y) && (p.y <= max.y)
                   && (p.z >= min.z) && (p.z <= max.z);
        }


    };
    inline std::ostream &operator << (std::ostream &os, const Box3 &b) {
        os << "min: " << b.min << "\n";
        os << "max: " << b.max;
        return os;
    }
}