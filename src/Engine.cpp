#include "Engine.h"

const sf::Time Engine::TimePerFrame = seconds(1.f / 60.f);

Engine::Engine() {
    resolution = Vector2u(1920, 1080);
    window.create(VideoMode(resolution.x, resolution.y), "Walled Garden", Style::Default);
    window.setFramerateLimit(FPS);
    _this_map = std::make_unique<Map>("test_map");
    _player = std::make_unique<Player>(_this_map.get(), sf::Vector2f(2000, 2000));

    _chunk_handler = std::make_unique<ChunkHandler>(_this_map.get(), _player->get_player_coordinates());
    view1.setCenter(_player->get_player_coordinates());
    view1.setSize(Vector2f(1920.f, 1080.f));
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
    window.draw(*_chunk_handler);
    window.display();
}

void Engine::input() {
    Event event{};

    while (window.pollEvent(event)) {
        // Window Closed
        if (event.type == Event::Closed) {
            window.close();
        }

        if ((event.type == Event::KeyPressed) && (Keyboard::isKeyPressed(Keyboard::Escape))) {
            window.close();
        }

        if ((event.type == Event::MouseButtonPressed) && (Mouse::isButtonPressed(Mouse::Left))) {
            last_mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            _chunk_handler->update_tile_map_at_pos(last_mouse_pos, current_block_type);
        }
        if ((event.type == Event::MouseButtonReleased) && (mouse_was_pressed)) {
            mouse_was_pressed = false;
            // do something
        }
    }
    // Definitely improve this
    sf::Vector2f movement_input = sf::Vector2f(0.f, 0.f);
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        movement_input.y -= 1.f;
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        movement_input.y += 1.f;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        movement_input.x += 1.f;
    }
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        movement_input.x -= 1.f;
    }
    _player->process_player(movement_input);
    _chunk_handler->update_chunks(_player->get_player_coordinates());
    view1.setCenter(_player->get_player_coordinates());
    window.setView(view1);
}