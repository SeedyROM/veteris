#pragma once

#include <cmath>
#include <iostream>

#include "Base.h"

namespace veteris {
    struct Point3 : BaseVector3 {
        using BaseVector3::BaseVector3;

        float distance_squared(const Point3& p) const {
            const float tx = x - p.x;
            const float ty = y - p.y;
            const float tz = z - p.z;
        }
        float distance(const Point3& p) const {
            return std::sqrt(distance_squared(p));
        }
    };
    inline std::ostream& operator<< (std::ostream &os, const Point3 &p) {
        os << "[" << p.x << ", " << p.y << ", " << p.z << "]";
        return os;
    }
}