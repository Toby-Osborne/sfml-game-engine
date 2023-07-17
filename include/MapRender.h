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
    unsigned int get_chunk_count();
    Chunk *get_chunk(unsigned int chunk_id);
    bool load(sf::Vector2f camera_coordinates);
private:
    static constexpr unsigned int _chunk_load_radius = 3;
    std::array<std::unique_ptr<Chunk>,((_chunk_load_radius*2-1)*(_chunk_load_radius*2-1))> _chunks;
};


#endif //CPPGAME_TEST_MAPRENDER_H
