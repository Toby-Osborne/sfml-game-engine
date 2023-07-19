#include "MapRender.h"

void MapRender::update_tile_map_at_pos(sf::Vector2f mouse_world_coords, uint8_t tile_id) {
    sf::Vector2i global_chunk_id =
            Chunk::get_chunk_coordinates_from_mouse_pos(mouse_world_coords);
    Chunk *chunk_to_change = _chunks->get_chunk(global_chunk_id);
    chunk_to_change->update_chunk_tile(mouse_world_coords, tile_id);
}

void MapRender::load(sf::Vector2f camera_coordinates) {
    _chunks = std::make_unique<ChunkQueue>(Chunk::get_chunk_coordinates_from_mouse_pos(camera_coordinates), _map);
}

Chunk *MapRender::get_chunk(sf::Vector2i chunk) {
    return _chunks->get_chunk(chunk);
}


MapRender::MapRender(std::shared_ptr<Map> map, sf::Vector2f player_coordinates) {
    _map = map;
    _chunk_origin_center = Chunk::get_chunk_coordinates_from_mouse_pos(player_coordinates);
    _chunks = std::make_unique<ChunkQueue>(_chunk_origin_center, map);

    _render_distance = _chunks->get_render_distance();
    _num_chunks = _render_distance * _render_distance;
}

void MapRender::update_chunks(sf::Vector2f player_world_coords) {
    sf::Vector2i player_chunk = Chunk::get_chunk_coordinates_from_mouse_pos(player_world_coords);
    switch (player_chunk.x - _chunk_origin_center.x) {
        case 1:
            if (_chunks->step(ChunkQueue::SIDE::X_RIGHT)) {
                _chunk_origin_center.x++;
            }
            return;
        case -1:
            if (_chunks->step(ChunkQueue::SIDE::X_LEFT)) {
                _chunk_origin_center.x--;
            }
            return;
        case 0:
            break;
        default:
            // reload chunks
            return;
    }
    switch (player_chunk.y - _chunk_origin_center.y) {
        case 1:
            if (_chunks->step(ChunkQueue::SIDE::Y_BOTTOM)) {
                _chunk_origin_center.y++;
            }
            return;
        case -1:
            if (_chunks->step(ChunkQueue::SIDE::Y_TOP)) {
                _chunk_origin_center.y--;
            }
            return;
        case 0:
            break;
        default:
            // reload chunks
            return;
    }
};