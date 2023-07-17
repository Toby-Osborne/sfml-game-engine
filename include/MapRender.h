#ifndef CPPGAME_TEST_MAPRENDER_H
#define CPPGAME_TEST_MAPRENDER_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "Map.h"
#include "Chunk.h"
#include <array>

class MapRender{
public:
    void update_tile_map_at_pos(sf::Vector2f mouse_world_coords,uint8_t tile_id);
    MapRender(std::string tileset, sf::Vector2u tileSize, std::shared_ptr<Map> map);
    int get_chunk_count();
    Chunk *get_chunk(sf::Vector2i chunk_id);
    Chunk *get_chunk(int i);
    bool load(sf::Vector2f camera_coordinates);
private:
    sf::Vector2i chunk_origin;
    static constexpr int _chunk_load_radius = 3;
    static constexpr int _array_width = _chunk_load_radius*2-1;
    static constexpr int _array_height = _chunk_load_radius*2-1;
    std::array<std::unique_ptr<Chunk>,(_array_width*_array_height)> _chunks;
};


#endif //CPPGAME_TEST_MAPRENDER_H
