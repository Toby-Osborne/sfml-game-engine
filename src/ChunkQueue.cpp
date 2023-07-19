#include "ChunkQueue.h"

#include <utility>

ChunkQueue::ChunkQueue(sf::Vector2i global_chunk_coordinates, std::shared_ptr<Map> map) {
    _map = map;
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
            _chunk_array[j % _render_distance][i % _render_distance] = std::make_unique<Chunk>(
                    Chunk(sf::Vector2i(i, j), _map));
        }
    }
}

Chunk *ChunkQueue::get_chunk(sf::Vector2i chunk_coordinates) {
    // add check here?
    Chunk *chunk = _chunk_array[chunk_coordinates.y % _render_distance][chunk_coordinates.x % _render_distance].get();
    return chunk;
}

Chunk *ChunkQueue::get_local_chunk(sf::Vector2i chunk) {
    return (_chunk_array[chunk.y][chunk.x].get());
}

void ChunkQueue::step(ChunkQueue::SIDE side) {
    switch (side) {
        case SIDE::X_LEFT:  // add to negative x-axis
        {
            if (_chunk_zero.x - 1 < 0) return;
            _chunk_zero.x--;
            for (int j = 0; j < _render_distance; j++) {
                _chunk_array[(_chunk_zero.y + j) % _render_distance][_chunk_zero.x %
                                                                     _render_distance] = std::make_unique<Chunk>(
                        sf::Vector2i(_chunk_zero.x, _chunk_zero.y + j), _map);
            }
        }
            break;
        case SIDE::X_RIGHT: // add to x axis
        {
            if (_chunk_zero.x + _render_distance >= _map->map_width() / CHUNK_SIZE_IN_TILES) return;
            for (int j = 0; j < _render_distance; j++) {
                _chunk_array[(_chunk_zero.y + j) % _render_distance][(_chunk_zero.x + _render_distance - 1) %
                                                                     _render_distance] = std::make_unique<Chunk>(
                        sf::Vector2i(_chunk_zero.x + _render_distance - 1, _chunk_zero.y + j), _map);
            }
            _chunk_zero.x++;
        }
            break;
        case SIDE::Y_BOTTOM:    // Add to y axis
            if (_chunk_zero.y + _render_distance >= _map->map_height() / CHUNK_SIZE_IN_TILES) return;
            _chunk_zero.y++;
            for (int i = 0; i < _render_distance; i++) {
                _chunk_array[(_chunk_zero.y + _render_distance - 1) % _render_distance][(_chunk_zero.x + i) %
                                                                                        _render_distance] = std::make_unique<Chunk>(
                        sf::Vector2i(_chunk_zero.x + i, _chunk_zero.y + _render_distance - 1), _map);
            }
            break;
        case SIDE::Y_TOP:
            if (_chunk_zero.y - 1 < 0) return;
            _chunk_zero.y--;
            for (int i = 0; i < _render_distance; i++) {
                _chunk_array[_chunk_zero.y % _render_distance][(_chunk_zero.x + i) %
                                                               _render_distance] = std::make_unique<Chunk>(
                        sf::Vector2i(_chunk_zero.x + i, _chunk_zero.y), _map);
            }
            break;
    }
}

const int ChunkQueue::get_render_distance() {
    return _render_distance;
}
