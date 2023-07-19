#ifndef CPPGAME_TEST_CHUNKQUEUE_H
#define CPPGAME_TEST_CHUNKQUEUE_H

#include "Chunk.h"
#include <SFML/Graphics.hpp>
#include <array>
#include "EngineDefines.h"

class ChunkQueue : public sf::Drawable{

private:
    sf::Vector2i _chunk_zero;
    std::shared_ptr<Map> _map;
    static constexpr int _render_distance = 5;

    sf::Texture _m_tileset;
    std::unique_ptr<Chunk> _chunk_array[_render_distance][_render_distance];

    std::unique_ptr<Chunk> _create_chunk(sf::Vector2i chunk_coordinates);

public:
    ChunkQueue(sf::Vector2i global_chunk_coordinates, std::shared_ptr<Map> map);

    static const int get_render_distance();

    enum SIDE {
        X_LEFT,
        X_RIGHT,
        Y_BOTTOM,
        Y_TOP
    };

    bool step(ChunkQueue::SIDE side);

    Chunk *get_chunk(sf::Vector2i chunk_coordinates);

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};


#endif //CPPGAME_TEST_CHUNKQUEUE_H
