#include <SFML/Graphics.hpp>
#include <random>

#include "tile_map.h"
#include "perlin_noise.h"

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    const uint32_t WINDOW_WIDTH = 1200;
    const uint32_t WINDOW_HEIGHT = 800;

    sf::RenderWindow window({WINDOW_WIDTH, WINDOW_HEIGHT},
                            "Cat Fighter",
                            sf::Style::Close,
                            settings);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution dist(0, 100);

    const uint32_t TILE_MAP_HEIGHT = 50;
    const uint32_t TILE_MAP_WIDTH = 75;

    auto map = new uint32_t *[TILE_MAP_HEIGHT];
    for (uint32_t y = 0; y < TILE_MAP_HEIGHT; ++y) {
        map[y] = new uint32_t[TILE_MAP_WIDTH];
        for (uint32_t x = 0; x < TILE_MAP_WIDTH; ++x) {
            double noise = perlin_noise_2_d(static_cast<float>(x),
                                            static_cast<float>(y),
                                            0.1,
                                            2,
                                            2009);

            if (noise < 0.5f) {
                map[y][x] = dist(mt) < 90 ? 1 : dist(mt) < 50 ? 3 : dist(mt) < 50 ? 4 : 2;
            } else {
                map[y][x] = 0;
            }
        }
    }

    tile_map tile_map;
    if (!tile_map.load(R"(..\..\..\resources\tile_set.png)",
                       {16, 16},
                       map,
                       TILE_MAP_WIDTH,
                       TILE_MAP_HEIGHT)) {
        return -1;
    }

    for (uint32_t y = 0; y < TILE_MAP_HEIGHT; ++y) {
        delete[] map[y];
    }

    delete[] map;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.draw(tile_map);
        window.display();
    }

    return 0;
}
