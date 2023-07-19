#ifndef CPPGAME_TEST_CHUNKQUEUE_H
#define CPPGAME_TEST_CHUNKQUEUE_H

#include "Chunk.h"
#include <SFML/Graphics.hpp>
#include <array>
#include "EngineDefines.h"

class ChunkQueue {

private:
    sf::Vector2i _chunk_zero;
    std::shared_ptr<Map> _map;
    static constexpr int _render_distance = 7;

    std::unique_ptr<Chunk> _chunk_array[_render_distance][_render_distance];

public:
    ChunkQueue(sf::Vector2i global_chunk_coordinates, std::shared_ptr<Map> map);

    Chunk *get_local_chunk(sf::Vector2i chunk);

    static const int get_render_distance();

    enum SIDE {
        X_LEFT,
        X_RIGHT,
        Y_BOTTOM,
        Y_TOP
    };

    void step(ChunkQueue::SIDE side);

    Chunk *get_chunk(sf::Vector2i chunk_coordinates);

    Chunk *get_first_chunk();   // For Rendering
};


#endif //CPPGAME_TEST_CHUNKQUEUE_H
