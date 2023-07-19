#include "Player.h"

Player::Player(Map *map) {
    _map = map;
    _chunk_handler = std::make_unique<ChunkHandler>(_map, _player_coordinates);
    _player_clock.restart();
}

sf::Vector2f Player::get_player_coordinates() {
    return this->_player_coordinates;
}

ChunkHandler *Player::get_chunk_handler() {
    return _chunk_handler.get();
}

inline static constexpr float sign(float val) { return val < 0 ? -1.0 : 1.0; }

void Player::_handle_player_physics(const sf::Vector2f &movement_input) {

    float dt = (float) (_player_clock.restart().asSeconds());
    // Handle X input
    if ((((velocity.x > 1.0) || (velocity.x < -1.0)) && (sign(velocity.x) != sign(movement_input.x))) ||
        (movement_input.x == 0)) {
        velocity.x *= 0.9;
        if ((velocity.x < vel_stop_threshold) && (velocity.x > -vel_stop_threshold)) {
            velocity.x = 0.f;
        }
    } else {
        if ((velocity.x < max_velocity) && (velocity.x > -max_velocity)) {
            velocity.x += acceleration_coefficient * (movement_input.x) * dt * inverse_mass;
        }
    }
    // Handle Y input
    if ((((velocity.y > 1.0) || (velocity.y < -1.0)) && (sign(velocity.y) != sign(movement_input.y))) ||
        (movement_input.y == 0)) {
        velocity.y *= 0.9;
        if ((velocity.y < vel_stop_threshold) && (velocity.y > -vel_stop_threshold)) {
            velocity.y = 0.f;
        }
    } else {
        if ((velocity.y < max_velocity) && (velocity.y > -max_velocity)) {
            velocity.y += acceleration_coefficient * (movement_input.y) * dt * inverse_mass;
        }
    }


    _player_coordinates.x += velocity.x * dt;
    _player_coordinates.y += velocity.y * dt;
}

void Player::process_player(const sf::Vector2f &movement_input) {
    _handle_player_physics(movement_input);
    _chunk_handler->update_chunks(_player_coordinates);
}