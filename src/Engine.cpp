#include "Engine.h"

const sf::Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine() : _this_map("test_map") {
    resolution = Vector2f(1920 , 1080);
    window.create(VideoMode(resolution.x, resolution.y), "Shit Game", Style::Default);
    window.setFramerateLimit(FPS);

    map.load("assets/tileset.png", sf::Vector2u(32, 32), _this_map.map_data(), _this_map.map_width(), _this_map.map_height());
    view1.setCenter(Vector2f(200.f,200.f));
    view1.setSize(Vector2f(1920.f,1920.f));
    window.setView(view1);
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

    // Draw the map on screen
    window.draw(map);
    window.display();
}

void Engine::input() {
    Event event{};

    while(window.pollEvent(event)) {
        // Window Closed
        if (event.type == Event::Closed) {
            window.close();
        }

        if ((event.type == Event::KeyPressed)&&(Keyboard::isKeyPressed(Keyboard::Escape))) {
            window.close();
        }
    }
    // Definitely improve this
    if (Keyboard::isKeyPressed(Keyboard::W)){
        view1.move(0,-1);
        window.setView(view1);
    }
    if (Keyboard::isKeyPressed(Keyboard::S)){
        view1.move(0,1);
        window.setView(view1);
    }
    if (Keyboard::isKeyPressed(Keyboard::D)){
        view1.move(1,0);
        window.setView(view1);
    }
    if (Keyboard::isKeyPressed(Keyboard::A)){
        view1.move(-1,0);
        window.setView(view1);
    }
}