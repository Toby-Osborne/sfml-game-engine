#ifndef CPPGAME_TEST_MAPRENDER_H
#define CPPGAME_TEST_MAPRENDER_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "Map.h"

class MapRender : public sf::Drawable, public sf::Transformable{
public:
    void update_tile_map_at_pos(sf::Vector2f mouse_world_coords,uint8_t tile_id);
    MapRender(std::string tileset, sf::Vector2u tileSize, std::shared_ptr<Map> map);
    bool load(sf::Vector2f camera_coordinates);
private:
    static constexpr uint32_t render_box_size_tiles = 100;   // Render a 19x19 box around the player

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    std::shared_ptr<Map> _this_map;

    sf::Vector2u _array_start;
    sf::Vector2u _array_dimensions;

    std::string _tileset;
    sf::Vector2u _tileSize;

};


#endif //CPPGAME_TEST_MAPRENDER_H
