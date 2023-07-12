#ifndef CPPGAME_TEST_TILEMAP_H
#define CPPGAME_TEST_TILEMAP_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>

class TileMap : public sf::Drawable, public sf::Transformable{
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const uint8_t* tiles, unsigned int width, unsigned int height);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};


#endif //CPPGAME_TEST_TILEMAP_H