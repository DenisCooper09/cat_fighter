#include <SFML/Graphics.hpp>

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    const uint32_t WINDOW_WIDTH = 1200;
    const uint32_t WINDOW_HEIGHT = 800;

    sf::RenderWindow window({WINDOW_WIDTH, WINDOW_HEIGHT},
                            "Cat Fighter",
                            sf::Style::Close,
                            settings);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.display();
    }

    return 0;
}
