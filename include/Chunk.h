#ifndef CPPGAME_TEST_CHUNK_H
#define CPPGAME_TEST_CHUNK_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "EngineDefines.h"

class Chunk {
private:
    sf::VertexArray _m_vertices;
    sf::Vector2i _array_start;

    sf::Vector2i _chunk_coordinates;

    Map *_this_map;
    sf::Texture *_m_tileset;

public:
    sf::VertexArray *get_vertices();

    static sf::Vector2i get_chunk_coordinates_from_mouse_pos(sf::Vector2f global_mouse_pos);

    void update_chunk_tile(sf::Vector2f mouse_world_coords, uint8_t tile_id);

    Chunk(sf::Vector2i chunk_location, Map *this_map, sf::Texture *tileset);
};


#endif //CPPGAME_TEST_CHUNK_H
