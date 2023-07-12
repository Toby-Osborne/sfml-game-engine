#ifndef CPPGAME_TEST_ENGINE_H
#define CPPGAME_TEST_ENGINE_H

#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include <SFML/Graphics/RectangleShape.hpp>

using namespace sf;
using namespace std;

class Engine {
private:
    Vector2f resolution;
    RenderWindow window;
    const unsigned int FPS = 60;
    static const Time TimePerFrame;
    TileMap map;
    View view1;
public:
    Engine();

    void input();

    void draw();

    // main loop which should be in the run function

    void run();
};


#endif //CPPGAME_TEST_ENGINE_H
