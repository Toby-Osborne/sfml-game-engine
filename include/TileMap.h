#ifndef CPPGAME_TEST_TILEMAP_H
#define CPPGAME_TEST_TILEMAP_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "Map.h"

class TileMap : public sf::Drawable, public sf::Transformable{
public:
    void update_tile_map_at_pos(sf::Vector2f mouse_world_coords,uint8_t tile_id);
    bool load(const std::string& tileset, sf::Vector2u tileSize, std::shared_ptr<Map> map);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    std::shared_ptr<Map> _this_map;
};


#endif //CPPGAME_TEST_TILEMAP_H
