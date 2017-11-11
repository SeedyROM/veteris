#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "geom/Transform.h"

namespace veteris {
    struct Triangle {
        sf::Color color;
        Point3 v0, v1, v2;
        Triangle(Point3 _v0, Point3 _v1, Point3 _v2)
                : v0(_v0), v1(_v1), v2(_v2), color(sf::Color(40, 250, 20)) {}

        operator sf::VertexArray() const {
            sf::VertexArray vs(sf::Triangles, 3);
            vs[0] = sf::Vertex(v0, color);
            vs[1] = sf::Vertex(v1, color);
            vs[2] = sf::Vertex(v2, color);

            return vs;
        }
    };
    
    struct Mesh {
        std::vector<Triangle> triangles;

        void transform(const Transform3& _transform) {
            for(auto &t : triangles) {
                t.v0 = _transform.transform(t.v0);
                t.v1 = _transform.transform(t.v1);
                t.v2 = _transform.transform(t.v2);
            }
        }
    };
}