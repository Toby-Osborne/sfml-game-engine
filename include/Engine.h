#ifndef CPPGAME_TEST_ENGINE_H
#define CPPGAME_TEST_ENGINE_H

#include <SFML/Graphics.hpp>
#include "ChunkHandler.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "Map.h"
#include "Player.h"

using namespace sf;
using namespace std;

class Engine {
private:
    Vector2u resolution;
    RenderWindow window;
    const unsigned int FPS = 60;
    static const Time TimePerFrame;
    unique_ptr<Map> _this_map;
    unique_ptr<Player> _player;
    View view1;

    sf::Vector2f last_mouse_pos;

    unique_ptr<ChunkHandler> _chunk_handler;

    /// For map editor, probably this entire thing needs re-factoring
    bool mouse_was_pressed = false;
    uint8_t current_block_type = 1;
public:
    Engine();

    void input();

    void draw();

    // main loop which should be in the run function

    void run();
};


#endif //CPPGAME_TEST_ENGINE_H
