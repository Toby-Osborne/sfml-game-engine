#include "../include/Engine.h"

const sf::Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine() {
    resolution = Vector2f(800,600);
    window.create(VideoMode(resolution.x, resolution.y), "Shit Game", Style::Default);
    window.setFramerateLimit(FPS);

    this->speed = 2;
    this->snakeDirection = RIGHT;

    timeSinceLastMove = Time::Zero;

    newSnake();
}

void Engine::run() {
    Clock clock;
    // Main loop of the game runs until the window is closed
    while (window.isOpen()) {
        Time dt = clock.restart();
        this->timeSinceLastMove += dt;

        draw();
        update();
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

        if (event.type == Event::KeyPressed) {
            switch(event.key.code) {
                case Keyboard::Escape:
                    window.close();
                    break;
                case Keyboard::Up:
                    addDirection(Direction::UP);
                    break;
                case Keyboard::Down:
                    addDirection(Direction::DOWN);
                    break;
                case Keyboard::Left:
                    addDirection(Direction::LEFT);
                    break;
                case Keyboard::Right:
                    addDirection(Direction::RIGHT);
                    break;
            }
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

void Engine::addDirection(int newDirection) {
    if (directionQueue.empty()) {
        directionQueue.emplace_back(newDirection);
    } else {
        if (directionQueue.back() != newDirection) {
            directionQueue.emplace_back(newDirection);
        }
    }
}

void Engine::update() {
    // We need to update the postiion
    if (timeSinceLastMove.asSeconds() >= seconds(1.f/float(speed)).asSeconds()) {
        Vector2f thisSectionPosition = snake[0].getPosition();
        Vector2f lastSectionPosition = thisSectionPosition;

        if (!directionQueue.empty()) {
            switch (snakeDirection) {
                case Direction::UP:
                    if (directionQueue.front() != Direction::DOWN) {
                        snakeDirection = directionQueue.front();
                    }
                    break;
                case Direction::DOWN:
                    if (directionQueue.front() != Direction::UP) {
                        snakeDirection = directionQueue.front();
                    }
                    break;
                case Direction::LEFT:
                    if (directionQueue.front() != Direction::RIGHT) {
                        snakeDirection = directionQueue.front();
                    }
                    break;
                case Direction::RIGHT:
                    if (directionQueue.front() != Direction::LEFT) {
                        snakeDirection = directionQueue.front();
                    }
                    break;
            }
            directionQueue.pop_front();
        }

        switch (snakeDirection) {
            case Direction::RIGHT:
                snake[0].setPosition(Vector2f(thisSectionPosition.x + 20, thisSectionPosition.y));
                break;
            case Direction::LEFT:
                snake[0].setPosition(Vector2f(thisSectionPosition.x - 20, thisSectionPosition.y));
                break;
            case Direction::UP:
                snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y - 20));
                break;
            case Direction::DOWN:
                snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y + 20));
                break;
        }
        for (int s = 1;s < snake.size();s++){
            thisSectionPosition = snake[s].getPosition();
            snake[s].setPosition(lastSectionPosition);
            lastSectionPosition = thisSectionPosition;
        };

        for (auto & s : snake) {
            s.update();
        }

        timeSinceLastMove = Time::Zero;
    }
}