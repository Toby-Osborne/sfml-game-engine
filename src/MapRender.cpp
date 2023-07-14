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
    this->load();
}

bool MapRender::load() {
    // load the tileset texture
    if (!m_tileset.loadFromFile(_tileset))
        return false;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(_this_map->map_width() * _this_map->map_height() * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < _this_map->map_width(); ++i)
        for (unsigned int j = 0; j < _this_map->map_height(); ++j)
        {
            // get the current tile number
            int tileNumber = _this_map->map_data()[i + j * _this_map->map_width()];

            // find its position in the tileset texture
            int tu = tileNumber;
            int tv = tileNumber;

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * _this_map->map_width()) * 4];

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