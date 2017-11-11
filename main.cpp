#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 400), "Veteris");

    while(window.isOpen()) {
        sf::Event e;
        while(window.pollEvent(e)) {
            if(e.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color(244, 120, 24));

        window.display();
    }

    return 0;
}