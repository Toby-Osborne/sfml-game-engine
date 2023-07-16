#include "MapRender.h"

void MapRender::update_tile_map_at_pos(sf::Vector2f mouse_world_coords, uint8_t tile_id) {
    uint32_t x_coord = mouse_world_coords.x/32;
    uint32_t y_coord = mouse_world_coords.y/32;
    sf::Vertex* quad = &m_vertices[(x_coord + y_coord * _this_map->map_width()) * 4];

    // find its position in the tileset texture
    int tu = tile_id % (m_tileset.getSize().x / 32);
    int tv = tile_id / (m_tileset.getSize().x / 32);

    // define its 4 texture coordinates
    quad[0].texCoords = sf::Vector2f(tu * 32, tv * 32);
    quad[1].texCoords = sf::Vector2f((tu + 1) * 32, tv * 32);
    quad[2].texCoords = sf::Vector2f((tu + 1) * 32, (tv + 1) * 32);
    quad[3].texCoords = sf::Vector2f(tu * 32, (tv + 1) * 32);
}

MapRender::MapRender(const std::string tileset, sf::Vector2u tileSize, std::shared_ptr<Map> map) {
    _tileset = tileset;
    _tileSize = tileSize;
    _this_map = std::move(map);
}

bool MapRender::load(sf::Vector2f camera_coordinates) {
    // load the tileset texture
    if (!m_tileset.loadFromFile(_tileset))
        return false;

    unsigned int x_tile_start;
    unsigned int y_tile_start;

    if (render_box_size_tiles > (unsigned int)(camera_coordinates.x/32)) {
        x_tile_start = 0;
    } else {
        x_tile_start = (camera_coordinates.x/32)-render_box_size_tiles;
    }

    if (render_box_size_tiles > (unsigned int)(camera_coordinates.y/32)) {
        y_tile_start = 0;
    } else {
        y_tile_start = (camera_coordinates.y/32)-render_box_size_tiles;
    }

    unsigned int array_width = ((unsigned int)(camera_coordinates.x/32) + render_box_size_tiles - x_tile_start);
    unsigned int array_height = ((unsigned int)(camera_coordinates.y/32) + render_box_size_tiles - y_tile_start);

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(array_width * array_height * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < array_width; ++i)
        for (unsigned int j = 0; j < array_height; ++j)
        {
            // get the current tile number
            int tileNumber = _this_map->map_data()[x_tile_start + i + j * (_this_map->map_width() + y_tile_start)];

            // find its position in the tileset texture
            int tu = tileNumber;
            int tv = tileNumber;

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * array_width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * _tileSize.x, j * _tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * _tileSize.x, j * _tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * _tileSize.x, (j + 1) * _tileSize.y);
            quad[3].position = sf::Vector2f(i * _tileSize.x, (j + 1) * _tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * _tileSize.x, tv * _tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, tv * _tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, (tv + 1) * _tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * _tileSize.x, (tv + 1) * _tileSize.y);
        }
    return true;
}

void MapRender::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}