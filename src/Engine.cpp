#include "Engine.h"

const sf::Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine() {
    resolution = Vector2f(1920 , 1080);
    window.create(VideoMode(resolution.x, resolution.y), "Walled Garden", Style::Default);
    window.setFramerateLimit(FPS);

    _this_map = std::make_shared<Map>("test_map");
    map.load("assets/tileset.png", sf::Vector2u(32, 32), _this_map);
    view1.setCenter(Vector2f(320.f,320.f));
    view1.setSize(Vector2f(1920.f,1080.f));
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

        if ((event.type == Event::MouseButtonPressed)&&(Mouse::isButtonPressed(Mouse::Left))) {
            last_mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            map.update_tile_map_at_pos(last_mouse_pos,1);
        }
        if ((event.type == Event::MouseButtonReleased)&&(mouse_was_pressed)) {
            mouse_was_pressed = false;
            // do something
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