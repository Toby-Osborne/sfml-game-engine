#ifndef CPPGAME_TEST_ENGINE_H
#define CPPGAME_TEST_ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <deque>

#include "SnakeSection.h"

using namespace sf;
using namespace std;

class Engine {
private:
    Vector2f resolution;
    RenderWindow window;
    const unsigned int FPS = 60;
    static const Time TimePerFrame;

    vector<SnakeSection> snake;

    int snakeDirection;
    deque<int> directionQueue;
    int speed;

    Time timeSinceLastMove;
public:
    enum Direction { RIGHT, DOWN, LEFT, UP };

    void addDirection(int newDirection);
    void update();

    Engine();

    void input();

    void draw();

    void newSnake();
    void addSnakeSection();

    // main loop which should be in the run function

    void run();
};


#endif //CPPGAME_TEST_ENGINE_H
