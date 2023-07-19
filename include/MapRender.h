#ifndef CPPGAME_TEST_MAPRENDER_H
#define CPPGAME_TEST_MAPRENDER_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "Map.h"
#include "Chunk.h"
#include "ChunkQueue.h"
#include <array>

class MapRender {
public:
    void update_tile_map_at_pos(sf::Vector2f mouse_world_coords, uint8_t tile_id);

    MapRender(std::shared_ptr<Map> map, sf::Vector2f player_coordinates);

    Chunk *get_chunk(sf::Vector2i chunk);

    void load(sf::Vector2f camera_coordinates);

    void update_chunks(sf::Vector2f player_world_coords);

    int get_num_chunks();

private:
    int _render_distance;
    int _num_chunks;
    std::unique_ptr<ChunkQueue> _chunks;
    sf::Vector2i _chunk_origin_center;
    std::shared_ptr<Map> _map;
};


#endif //CPPGAME_TEST_MAPRENDER_H
