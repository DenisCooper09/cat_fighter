#include "tile_map.h"

void tile_map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &_tile_set;
    target.draw(_vertices, states);
}

[[maybe_unused]] bool tile_map::load(const std::string &tile_set,
                                     sf::Vector2<uint32_t> tile_size,
                                     uint32_t **tiles,
                                     uint32_t width,
                                     uint32_t height) {
    std::filesystem::path tile_set_path = std::filesystem::current_path() / tile_set;
    if (!_tile_set.loadFromFile(tile_set_path.string())) {
        return false;
    }

    _vertices.setPrimitiveType(sf::Quads);
    _vertices.resize(width * height * 4);

    for (uint32_t x = 0; x < width; ++x) {
        for (uint32_t y = 0; y < height; ++y) {
            uint32_t tile_number = tiles[y][x];

            uint32_t tu = tile_number % (_tile_set.getSize().x / tile_size.x);
            uint32_t tv = tile_number / (_tile_set.getSize().x / tile_size.x);

            sf::Vertex *quad = &_vertices[(x + y * width) * 4];

            quad[0].position = static_cast<sf::Vector2f>(
                    sf::Vector2<uint32_t>(x * tile_size.x, y * tile_size.y));
            quad[1].position = static_cast<sf::Vector2f>(sf::Vector2<uint32_t>(
                    (x + 1) * tile_size.x, y * tile_size.y));
            quad[2].position = static_cast<sf::Vector2f>(sf::Vector2<uint32_t>(
                    (x + 1) * tile_size.x, (y + 1) * tile_size.y));
            quad[3].position = static_cast<sf::Vector2f>(sf::Vector2<uint32_t>(
                    x * tile_size.x, (y + 1) * tile_size.y));

            quad[0].texCoords = static_cast<sf::Vector2f>(sf::Vector2<uint32_t>(
                    tu * tile_size.x, tv * tile_size.y));
            quad[1].texCoords = static_cast<sf::Vector2f>(sf::Vector2<uint32_t>(
                    (tu + 1) * tile_size.x, tv * tile_size.y));
            quad[2].texCoords = static_cast<sf::Vector2f>(sf::Vector2<uint32_t>(
                    (tu + 1) * tile_size.x, (tv + 1) * tile_size.y));
            quad[3].texCoords = static_cast<sf::Vector2f>(sf::Vector2<uint32_t>(
                    tu * tile_size.x, (tv + 1) * tile_size.y));
        }
    }

    return true;
}
