#include "ChunkHandler.h"

void ChunkHandler::update_tile_map_at_pos(sf::Vector2f mouse_world_coords, uint8_t tile_id) {
    sf::Vector2i global_chunk_id =
            Chunk::get_chunk_coordinates_from_mouse_pos(mouse_world_coords);
    Chunk *chunk_to_change = get_chunk(global_chunk_id);
    chunk_to_change->update_chunk_tile(mouse_world_coords, tile_id);
}

ChunkHandler::ChunkHandler(Map *map, sf::Vector2f player_coordinates) {
    sf::Vector2i global_chunk_coordinates = Chunk::get_chunk_coordinates_from_mouse_pos(player_coordinates);
    _map = map;
    _chunk_origin_center = Chunk::get_chunk_coordinates_from_mouse_pos(player_coordinates);

    _map = map;
    _m_tileset.loadFromFile(TILESET);
    int i_start = global_chunk_coordinates.x - _render_distance / 2;
    int i_end = global_chunk_coordinates.x + _render_distance / 2 + 1;
    int j_start = global_chunk_coordinates.y - _render_distance / 2;
    int j_end = global_chunk_coordinates.y + _render_distance / 2 + 1;

    _chunk_zero = sf::Vector2i(i_start, j_start);

    // add check here
    for (int i = i_start;
         i < i_end; i++) {
        for (int j = j_start;
             j < j_end; j++) {
            _chunk_array[j % _render_distance][i % _render_distance] = _create_chunk(sf::Vector2i(i, j));
        }
    }
}

Chunk *ChunkHandler::get_chunk(sf::Vector2i chunk_coordinates) {
    // add check here?
    Chunk *chunk = _chunk_array[chunk_coordinates.y % _render_distance][chunk_coordinates.x % _render_distance].get();
    return chunk;
}


std::unique_ptr<Chunk> ChunkHandler::_create_chunk(sf::Vector2i chunk_coordinates) {
    return std::move(std::make_unique<Chunk>(chunk_coordinates, _map, &_m_tileset));
}

void ChunkHandler::update_chunks(sf::Vector2f player_world_coords) {
    sf::Vector2i player_chunk = Chunk::get_chunk_coordinates_from_mouse_pos(player_world_coords);
    switch (player_chunk.x - _chunk_origin_center.x) {
        case 1:
            if (step(SIDE::X_RIGHT)) {
                _chunk_origin_center.x++;
            }
            return;
        case -1:
            if (step(SIDE::X_LEFT)) {
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
            if (step(SIDE::Y_BOTTOM)) {
                _chunk_origin_center.y++;
            }
            return;
        case -1:
            if (step(SIDE::Y_TOP)) {
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

bool ChunkHandler::step(SIDE side) {
    switch (side) {
        case SIDE::X_LEFT:  // add to negative x-axis
        {
            if (_chunk_zero.x - 1 < 0) return false;
            _chunk_zero.x--;
            for (int j = 0; j < _render_distance; j++) {
                _chunk_array[(_chunk_zero.y + j) % _render_distance][_chunk_zero.x %
                                                                     _render_distance] = _create_chunk(
                        sf::Vector2i(_chunk_zero.x, _chunk_zero.y + j));
            }
        }
            break;
        case SIDE::X_RIGHT: // add to x axis
        {
            if (_chunk_zero.x + _render_distance >= _map->map_width() / CHUNK_SIZE_IN_TILES) return false;
            _chunk_zero.x++;
            for (int j = 0; j < _render_distance; j++) {
                _chunk_array[(_chunk_zero.y + j) % _render_distance][(_chunk_zero.x + _render_distance - 1) %
                                                                     _render_distance] = _create_chunk(
                        sf::Vector2i(_chunk_zero.x + _render_distance - 1, _chunk_zero.y + j));
            }
        }
            break;
        case SIDE::Y_BOTTOM:    // Add to y axis
            if (_chunk_zero.y + _render_distance >= _map->map_height() / CHUNK_SIZE_IN_TILES) return false;
            _chunk_zero.y++;
            for (int i = 0; i < _render_distance; i++) {
                _chunk_array[(_chunk_zero.y + _render_distance - 1) % _render_distance][(_chunk_zero.x + i) %
                                                                                        _render_distance] = _create_chunk(
                        sf::Vector2i(_chunk_zero.x + i, _chunk_zero.y + _render_distance - 1));
            }
            break;
        case SIDE::Y_TOP:
            if (_chunk_zero.y - 1 < 0) return false;
            _chunk_zero.y--;
            for (int i = 0; i < _render_distance; i++) {
                _chunk_array[_chunk_zero.y % _render_distance][(_chunk_zero.x + i) %
                                                               _render_distance] = _create_chunk(
                        sf::Vector2i(_chunk_zero.x + i, _chunk_zero.y));
            }
            break;
    }
    return true;
}

void ChunkHandler::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the tileset texture
    states.texture = &_m_tileset;

    for (const auto &i: _chunk_array) {
        for (const auto &j: i) {
            target.draw(*(j->get_vertices()), states);
        }
    }
}