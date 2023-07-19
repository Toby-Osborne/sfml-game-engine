#include "Engine.h"

const sf::Time Engine::TimePerFrame = seconds(1.f / 60.f);

Engine::Engine() {
    resolution = Vector2f(1920, 1080);
    window.create(VideoMode(resolution.x, resolution.y), "Walled Garden", Style::Default);
    window.setFramerateLimit(FPS);
    _this_map = std::make_shared<Map>("test_map");
    _player = std::make_unique<Player>(_this_map);
    _render_map = _player->get_map();
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
    for (int i = 0; i < 7; i++) {   // Fix magic number
        for (int j = 0; j < 7; j++) {
            Chunk *chunk = _render_map->get_chunk(sf::Vector2i(j, i));
            window.draw(*(chunk));
        }
    }
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
            _render_map->update_tile_map_at_pos(last_mouse_pos, current_block_type);
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
    view1.setCenter(_player->get_player_coordinates());
    window.setView(view1);
}