#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <geom/Transform.h>
#include <geom/Mesh.h>

using namespace veteris;


int main() {

    //auto t = Transform3::rotate(0, 0, (float)M_PI / 2.f);
    auto t = Transform3::scale(200, 200, 200);

    Mesh cube;
    cube.triangles.push_back(
            Triangle(
                    Point3(0.0f, 0.0f, 0.0f),
                    Point3(0.0f, 1.0f, 0.0f),
                    Point3(1.0f, 0.0f, 0.0f)
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

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Veretis", sf::Style::Default, settings);
    window.setFramerateLimit(120);

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
            window.draw(t);
        }
        window.display();

        cube.transform(Transform3::rotate(0.0001, 0.002, 0.003));
    }

    return 0;
}
