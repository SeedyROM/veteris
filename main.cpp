#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <geom/Transform.h>
#include <geom/Mesh.h>

using namespace veteris;



int main() {
    //auto t = Transform3::rotate(0, 0, (float)M_PI / 2.f);
    auto t = Transform3::scale(100, 100, 100);

    Mesh cube;
    cube.triangles.push_back(
            Triangle(
                    Point3(0, 0, 0),
                    Point3(0, 1, 0),
                    Point3(1, 0, 0)
            )
    );
    cube.triangles.push_back(
            Triangle(
                    Point3(1, 0, 1),
                    Point3(0, 1, 0),
                    Point3(1, 0, 0)
            )
    );
    cube.triangles.push_back(
            Triangle(
                    Point3(1, 0, 0),
                    Point3(0, 0, 1),
                    Point3(1, 1, 1)
            )
    );
    cube.transform(t);

    sf::RenderWindow window(sf::VideoMode(600, 400), "Veteris");
    window.setFramerateLimit(60);

    float cx = window.getSize().x / 2;
    float cy = window.getSize().y / 2;

    while(window.isOpen()) {
        sf::Event e;
        while(window.pollEvent(e)) {
            if(e.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color(244, 120, 24));
        for(auto t : cube.triangles) {
//            sf::ConvexShape s;
//            s.setFillColor(sf::Color(255,255,255));
//            s.setPointCount(3);
//            s.setPoint(0, t.v0.asVector2f(cx, cy));
//            s.setPoint(1, t.v1.asVector2f(cx, cy));
//            s.setPoint(2, t.v2.asVector2f(cx, cy));
            sf::Vertex tri[] = {
                    sf::Vertex(t.v0.asVector2f(cx, cy), t.color),
                    sf::Vertex(t.v1.asVector2f(cx, cy), t.color),
                    sf::Vertex(t.v2.asVector2f(cx, cy), t.color)
            };
            window.draw(tri, 3, sf::Triangles);
        }
        window.display();

        cube.transform(Transform3::rotate(0.001, 0.002, 0.003));
    }

    return 0;
}