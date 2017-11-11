#pragma once

#include <iostream>
#include <cmath>

#include "Base.h"
#include "Vector.h"

namespace veteris {
    struct Normal3 : public BaseVector3 {
        using BaseVector3::BaseVector3;

        float length_squared() const {
            return x*x + y*y + z*z;
        }
        float length() const {
            return sqrtf(length_squared());
        }
        void normalize() {
            float inv = 1.0f / length();
            x *= inv;
            y *= inv;
            z *= inv;
        }
    };

    inline std::ostream &operator << (std::ostream &os, const Normal3 &n) {
        os << "[" << n.x << ", " << n.y << ", " << n.z << "]";
        return os;
    }
}