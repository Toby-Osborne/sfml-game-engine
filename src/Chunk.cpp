#include "Chunk.h"
#include "EngineDefines.h"
#include <string>

sf::Vector2i Chunk::get_chunk_coordinates_from_mouse_pos(sf::Vector2f global_mouse_pos) {
    sf::Vector2i chunk_coords = sf::Vector2i((int) global_mouse_pos.x / (CHUNK_SIZE_IN_PIXELS),
                                             (int) global_mouse_pos.y / (CHUNK_SIZE_IN_PIXELS));
    return chunk_coords;
}


Chunk::Chunk(sf::Vector2i chunk_location, std::shared_ptr<Map> this_map, sf::Texture *tileset) {
    _this_map = this_map;
    _m_tileset = tileset;
    _chunk_coordinates = std::move(chunk_location);
    _array_start.x = _chunk_coordinates.x * CHUNK_SIZE_IN_TILES;
    _array_start.y = _chunk_coordinates.y * CHUNK_SIZE_IN_TILES;

    // resize the vertex array to fit the level size
    _m_vertices.setPrimitiveType(sf::Quads);
    _m_vertices.resize(CHUNK_SIZE_IN_TILES * CHUNK_SIZE_IN_TILES * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < CHUNK_SIZE_IN_TILES; ++i) {
        for (unsigned int j = 0; j < CHUNK_SIZE_IN_TILES; ++j) {
            // get the current tile number
            int tile_id = _this_map->map_data()[_array_start.x + i + (j + _array_start.y) * (_this_map->map_width())];

            // find its position in the tileset texture
            int tu = tile_id % (_m_tileset->getSize().x / TILE_SIZE);
            int tv = tile_id / (_m_tileset->getSize().x / TILE_SIZE);

            // get a pointer to the current tile's quad
            sf::Vertex *quad = &_m_vertices[(i + j * CHUNK_SIZE_IN_TILES) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f((float) (_array_start.x + i) * TILE_SIZE,
                                            (float) (_array_start.y + j) * TILE_SIZE);
            quad[1].position = sf::Vector2f((float) (_array_start.x + i + 1) * TILE_SIZE,
                                            (float) (_array_start.y + j) * TILE_SIZE);
            quad[2].position = sf::Vector2f((float) (_array_start.x + i + 1) * TILE_SIZE,
                                            (float) (_array_start.y + j + 1) * TILE_SIZE);
            quad[3].position = sf::Vector2f((float) (_array_start.x + i) * TILE_SIZE,
                                            (float) (_array_start.y + j + 1) * TILE_SIZE);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * TILE_SIZE, tv * TILE_SIZE);
            quad[1].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, tv * TILE_SIZE);
            quad[2].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, (tv + 1) * TILE_SIZE);
            quad[3].texCoords = sf::Vector2f(tu * TILE_SIZE, (tv + 1) * TILE_SIZE);
        }
    }
}

void Chunk::update_chunk_tile(sf::Vector2f mouse_world_coords, uint8_t tile_id) {
    int x_coord = (int) (mouse_world_coords.x / TILE_SIZE);
    int y_coord = (int) (mouse_world_coords.y / TILE_SIZE);

    if (x_coord > _this_map->map_width() || (y_coord > _this_map->map_height())) {
        return;
    }

    _this_map->update_map(x_coord, y_coord, tile_id);
    sf::Vertex *quad = &_m_vertices[(x_coord - _array_start.x + (y_coord - _array_start.y) * (CHUNK_SIZE_IN_TILES)) *
                                    4];

    // find its position in the tileset texture
    int tu = (int) tile_id % (_m_tileset->getSize().x / TILE_SIZE);
    int tv = (int) tile_id / (_m_tileset->getSize().x / TILE_SIZE);

    // define its 4 texture coordinates
    quad[0].texCoords = sf::Vector2f((float) tu * TILE_SIZE, (float) tv * TILE_SIZE);
    quad[1].texCoords = sf::Vector2f((float) (tu + 1) * TILE_SIZE, (float) tv * TILE_SIZE);
    quad[2].texCoords = sf::Vector2f((float) (tu + 1) * TILE_SIZE, (float) (tv + 1) * TILE_SIZE);
    quad[3].texCoords = sf::Vector2f((float) tu * TILE_SIZE, (float) (tv + 1) * TILE_SIZE);
}

void Chunk::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the transform
//    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = _m_tileset;

    // draw the vertex array
    target.draw(_m_vertices, states);
}
