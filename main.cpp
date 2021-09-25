#include <iostream>
#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Proyecto Info II");
    sf::CircleShape shape(100.f);
    sf::Texture texture;
    sf::Sprite image;

    if (!texture.loadFromFile("assets/image.png")) {
        std::cout << "Error al cargar textura, verifique la ruta";
        return EXIT_FAILURE;
    }
    image.setTexture(texture);
    image.setPosition((800 - 680) / 2, 0);

    window.setFramerateLimit(30);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition((800 - 200) / 2, 300);

    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Update world parameters

        // player.move(3,4);

        // Draw all elements
        window.clear();
        window.draw(shape);
        window.draw(image);
        window.display();
    }
    return 0;
}