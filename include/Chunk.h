#ifndef CPPGAME_TEST_CHUNK_H
#define CPPGAME_TEST_CHUNK_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Map.h"

class Chunk : public sf::Drawable, public sf::Transformable {
private:
    sf::VertexArray _m_vertices;
    sf::Vector2i _array_start;

    sf::Vector2i _chunk_coordinates;

    std::shared_ptr<Map> _this_map;
    sf::Texture _m_tileset;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:

    static sf::Vector2i get_chunk_coordinates_from_mouse_pos(sf::Vector2f global_mouse_pos);

    void update_chunk_tile(sf::Vector2f mouse_world_coords, uint8_t tile_id);

    Chunk(sf::Vector2i chunk_location, std::shared_ptr<Map> this_map);
};


#endif //CPPGAME_TEST_CHUNK_H
