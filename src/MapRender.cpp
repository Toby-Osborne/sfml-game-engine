#include "MapRender.h"

void MapRender::update_tile_map_at_pos(sf::Vector2f mouse_world_coords, uint8_t tile_id) {
    sf::Vector2i local_chunk_id = Chunk::get_chunk_coordinates_from_mouse_pos(mouse_world_coords) - chunk_origin;
    Chunk *chunk_to_change = this->get_chunk(local_chunk_id);
    chunk_to_change->update_chunk_tile(mouse_world_coords,tile_id);
}

int MapRender::get_chunk_count() {
    return _chunks.size();
}

Chunk *MapRender::get_chunk(sf::Vector2i chunk_id) {
    if (chunk_id.x*chunk_id.y > _chunks.size()) {
        return nullptr;
    } else {
        int index = chunk_id.y+(_array_height>>1) * _array_width + (chunk_id.x+_array_width>>1);
        return _chunks[index].get();
    }
}

Chunk *MapRender::get_chunk(int i) {
    return _chunks[i].get();
}

bool MapRender::load(sf::Vector2f camera_coordinates) {
    chunk_origin = Chunk::get_chunk_coordinates_from_mouse_pos(camera_coordinates);
    for (int i = 0;i<_array_width;i++){
        for (int j = 0;j<_array_height;j++) {
            sf::Vector2i chunk_coordinates = sf::Vector2i(chunk_origin.x+i-_chunk_load_radius+1,chunk_origin.y+j-_chunk_load_radius+1);
            _chunks[i+j*(_array_width)]->load(chunk_coordinates);
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