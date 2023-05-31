#ifndef CAT_FIGHTER_TILE_MAP_H
#define CAT_FIGHTER_TILE_MAP_H

#include <SFML/Graphics.hpp>
#include <filesystem>

class [[maybe_unused]] tile_map : public sf::Drawable, public sf::Transformable {
private:
    sf::VertexArray _vertices;
    sf::Texture _tile_set;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    [[maybe_unused]] bool load(const std::string& tile_set,
                               sf::Vector2<uint32_t> tile_size,
                               uint32_t **tiles,
                               uint32_t width,
                               uint32_t height);
};

#endif
