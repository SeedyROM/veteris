#pragma once

#include <SFML/Graphics.hpp>

namespace veteris {
    struct BaseVector3 : public sf::Vector3<float> {
        using sf::Vector3<float>::Vector3;

        // Iterative member access.
        float operator [] (int i) const {
            return (&x)[i];
        }
        float &operator [] (int i) {
            return (&x)[i];
        }
        // Implicit conversions to SFML.
        operator sf::Vector2f() const {
            return sf::Vector2f(x, y);
        }
        operator sf::Vector3f() const {
            return sf::Vector3f(x, y, z);
        }
    };
}
