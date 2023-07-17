#ifndef CPPGAME_TEST_CHUNK_H
#define CPPGAME_TEST_CHUNK_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "Map.h"

class Chunk : public sf::Drawable, public sf::Transformable{
private:
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    sf::Vector2u _array_start;
    sf::Vector2u _array_dimensions;

    std::string _tileset;

    std::shared_ptr<Map> _this_map;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    bool load(sf::Vector2u chunk_coordinates);
    void update_chunk_tile(sf::Vector2f mouse_world_coords,uint8_t tile_id);
    Chunk(std::string tileset, sf::Vector2u tileSize, std::shared_ptr<Map> map);
    static sf::Vector2u get_chunk_coordinates_from_mouse_pos(sf::Vector2f global_mouse_pos);
};


#endif //CPPGAME_TEST_CHUNK_H
