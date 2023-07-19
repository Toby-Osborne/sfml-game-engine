#ifndef CPPGAME_TEST_CHUNKHANDLER_H
#define CPPGAME_TEST_CHUNKHANDLER_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "Map.h"
#include "Chunk.h"
#include <array>

class ChunkHandler : public sf::Drawable {
public:
    void update_tile_map_at_pos(sf::Vector2f mouse_world_coords, uint8_t tile_id);

    Chunk *get_chunk(sf::Vector2i chunk);

    void update_chunks(sf::Vector2f player_world_coords);

    ChunkHandler(Map *map, sf::Vector2f player_coordinates);

    enum SIDE {
        X_LEFT,
        X_RIGHT,
        Y_BOTTOM,
        Y_TOP
    };

    bool step(SIDE side);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Vector2i _chunk_origin_center;
    Map *_map;

    sf::Vector2i _chunk_zero;
    static constexpr int _render_distance = 5;

    sf::Texture _m_tileset;
    std::unique_ptr<Chunk> _chunk_array[_render_distance][_render_distance];

    std::unique_ptr<Chunk> _create_chunk(sf::Vector2i chunk_coordinates);
};


#endif //CPPGAME_TEST_CHUNKHANDLER_H
