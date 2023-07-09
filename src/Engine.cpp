#include "../include/Engine.h"

const sf::Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine() {
    resolution = Vector2f(800,600);
    window.create(VideoMode(resolution.x, resolution.y), "Shit Game", Style::Default);
    window.setFramerateLimit(FPS);

    newSnake();
}

void Engine::run() {
    // Main loop of the game runs until the window is closed
    while (window.isOpen()) {
        draw();
        input();
    }
}

void Engine::draw() {
    window.clear(Color::Black);
    // Draw all snake sections
    for (auto & s : snake){
        window.draw(s.getShape());
    }
    window.display();
}

void Engine::input() {
    Event event{};

    while(window.pollEvent(event)) {
        // Window Closed
        if (event.type == Event::Closed) {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
    }
}

void Engine::newSnake() {
    snake.clear();
    snake.emplace_back(Vector2f(100,100));
    snake.emplace_back(Vector2f(80,100));
    snake.emplace_back(Vector2f(60,100));
}

void Engine::addSnakeSection() {
    Vector2f newSectionPosition = snake.back().getPosition();
    snake.emplace_back(newSectionPosition);
}