#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <geom/Transform.h>
#include <geom/Mesh.h>

using namespace veteris;

static float DIST = 1.666;

int main() {

    //auto t = Transform3::rotate(0, 0, (float)M_PI / 2.f);

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
    auto t = Transform3::scale(100, 100, 200);
    cube.transform(t);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Veretis", sf::Style::Default, settings);
    window.setFramerateLimit(120);

    sf::RenderTexture s;
    s.create(window.getSize().x / DIST, window.getSize().y / DIST);

    while(window.isOpen()) {
        sf::Event e;
        while(window.pollEvent(e)) {
            if(e.type == sf::Event::Closed) {
                window.close();
            }
        }

        s.clear(sf::Color(0, 0, 0, 0));
        for(auto t : cube.triangles) {
            s.draw(t);
        }
        s.display();

        window.clear(sf::Color(244, 120, 24));

        sf::Sprite sprite(s.getTexture());
        sprite.setScale(DIST, DIST);
        window.draw(sprite);

        window.display();

        cube.transform(Transform3::rotate(0.0001, 0.002, 0.003));
    }

    return 0;
}
