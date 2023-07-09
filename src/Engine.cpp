#include "../include/Engine.h"

const sf::Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine() {
    resolution = Vector2f(800,600);
    window.create(VideoMode(resolution.x, resolution.y), "Shit Game", Style::Default);
    window.setFramerateLimit(FPS);
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