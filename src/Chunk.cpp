#include "Chunk.h"
#include "EngineDefines.h"
sf::Vector2u Chunk::get_chunk_coordinates_from_mouse_pos(sf::Vector2f global_mouse_pos) {
    return sf::Vector2u((unsigned int)global_mouse_pos.x/(CHUNK_SIZE_IN_PIXELS),(unsigned int)global_mouse_pos.y/(CHUNK_SIZE_IN_PIXELS));
}

bool Chunk::load(sf::Vector2u chunk_coordinates) {
    // load the tileset texture
    if (!m_tileset.loadFromFile(_tileset))
        return false;

    _array_start.x = chunk_coordinates.x*CHUNK_SIZE_IN_TILES;
    _array_start.y = chunk_coordinates.y*CHUNK_SIZE_IN_TILES;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(CHUNK_SIZE_IN_TILES * CHUNK_SIZE_IN_TILES * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < CHUNK_SIZE_IN_TILES; ++i)
        for (unsigned int j = 0; j < CHUNK_SIZE_IN_TILES; ++j)
        {
            // get the current tile number
            int tile_id = _this_map->map_data()[_array_start.x + i + (j+_array_start.y) * (_this_map->map_width())];

            // find its position in the tileset texture
            int tu = tile_id % (m_tileset.getSize().x / TILE_SIZE);
            int tv = tile_id / (m_tileset.getSize().x / TILE_SIZE);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * CHUNK_SIZE_IN_TILES) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f((_array_start.x + i) * TILE_SIZE, (_array_start.y + j) * TILE_SIZE);
            quad[1].position = sf::Vector2f((_array_start.x + i + 1) * TILE_SIZE, (_array_start.y + j) * TILE_SIZE);
            quad[2].position = sf::Vector2f((_array_start.x + i + 1) * TILE_SIZE, (_array_start.y + j + 1) * TILE_SIZE);
            quad[3].position = sf::Vector2f((_array_start.x + i) * TILE_SIZE, (_array_start.y + j + 1) * TILE_SIZE);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * TILE_SIZE, tv * TILE_SIZE);
            quad[1].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, tv * TILE_SIZE);
            quad[2].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, (tv + 1) * TILE_SIZE);
            quad[3].texCoords = sf::Vector2f(tu * TILE_SIZE, (tv + 1) * TILE_SIZE);
        }
    return true;
}

Chunk::Chunk(std::string tileset, sf::Vector2u tileSize, std::shared_ptr<Map> map) {
    _tileset = tileset;
    _this_map = std::move(map);
}

void Chunk::update_chunk_tile(sf::Vector2f mouse_world_coords,uint8_t tile_id) {
    uint32_t x_coord = (unsigned int )(mouse_world_coords.x/32)+_array_start.x;
    uint32_t y_coord = (unsigned int )(mouse_world_coords.y/32)+_array_start.y;

    if (x_coord > _this_map->map_width()||(y_coord > _this_map->map_height())) {
        return;
    }

    _this_map->update_map(x_coord,y_coord,tile_id);

    sf::Vertex* quad = &m_vertices[(x_coord-_array_start.x + (y_coord-_array_start.y) * (_array_dimensions.x)) * 4];

    // find its position in the tileset texture
    int tu = tile_id % (m_tileset.getSize().x / 32);
    int tv = tile_id / (m_tileset.getSize().x / 32);

    // define its 4 texture coordinates
    quad[0].texCoords = sf::Vector2f(tu * 32, tv * 32);
    quad[1].texCoords = sf::Vector2f((tu + 1) * 32, tv * 32);
    quad[2].texCoords = sf::Vector2f((tu + 1) * 32, (tv + 1) * 32);
    quad[3].texCoords = sf::Vector2f(tu * 32, (tv + 1) * 32);
}

void Chunk::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}
