#include "MapRender.h"

void MapRender::update_tile_map_at_pos(sf::Vector2f mouse_world_coords, uint8_t tile_id) {
    int debug = 0;
}

unsigned int MapRender::get_chunk_count() {
    return _chunks.size();
}

Chunk *MapRender::get_chunk(unsigned int chunk_id) {
    if (chunk_id > _chunks.size()) {
        return nullptr;
    } else {
        return _chunks[chunk_id].get();
    }
}

bool MapRender::load(sf::Vector2f camera_coordinates) {
    sf::Vector2u chunk_origin = Chunk::get_chunk_coordinates_from_mouse_pos(camera_coordinates);
    for (int i = 0;i<2*_chunk_load_radius-1;i++){
        for (int j = 0;j<2*_chunk_load_radius-1;j++) {
            _chunks[i+j*(2*_chunk_load_radius-1)]->load(sf::Vector2u(chunk_origin.x+i-_chunk_load_radius+1,chunk_origin.y+j-_chunk_load_radius+1));
        }
    }
    return true;
}


MapRender::MapRender(const std::string tileset, sf::Vector2u tileSize, std::shared_ptr<Map> map) {
    for (int i = 0;i<2*_chunk_load_radius-1;i++){
        for (int j = 0;j<2*_chunk_load_radius-1;j++) {
            _chunks[i+j*(2*_chunk_load_radius-1)] = std::make_unique<Chunk>(tileset, tileSize, map);
        }
    }
}