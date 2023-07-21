#include "Player.h"

Player::Player(Map *map, sf::Vector2f spawn_pos) : Entity::Entity(map, default_player_hitbox, spawn_pos) {
    _map = map;
    _player_clock.restart();
}

void Player::_handle_player_physics(const sf::Vector2f &movement_input) {

    sf::Vector2f _player_coordinates = Entity::get_entity_coordinates();

    float dt = (float) (_player_clock.restart().asSeconds());
    // Handle X input

    if (movement_input.x == 0) {
        if ((velocity.x < vel_stop_threshold) && (velocity.x > -vel_stop_threshold)) {
            velocity.x = 0.f;
        } else {
            velocity.x *= 0.9;
        }
    } else {
        if ((velocity.x < max_velocity) && (velocity.x > -max_velocity)) {
            velocity.x += acceleration_coefficient * (movement_input.x) * dt * inverse_mass;
        }
    }
    // Handle Y input
    if ((velocity.y == 0) && ((movement_input.y < 0.f) && !jumped)) {
        velocity.y -= jump_velocity;    // Essentially adds energy to velocity
        jumped = true;
    } else {
        velocity.y += gravity * dt;
    }

    // Handle Collisions

    if (will_collide_x(velocity.x * dt * TILE_SIZE)) {
        velocity.x = 0;
    } else {
        _player_coordinates.x += velocity.x * dt * TILE_SIZE;
    }


    if (will_collide_y(velocity.y * dt * TILE_SIZE)) {
        if (velocity.y * dt > 0) jumped = false;    // If hitting the ground
        velocity.y = 0;
    } else {
        _player_coordinates.y += velocity.y * dt * TILE_SIZE;
    }

    Entity::set_entity_coordinates(_player_coordinates);
}


void Player::process_entity() {
    _handle_player_physics(_joystick);
}


void Player::process_player_input(const sf::Vector2f &joystick) {
    _joystick = joystick;
}


void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the tileset texture
//    states.texture = &_m_tileset;

//    for (const auto &i: _chunk_array) {
//        for (const auto &j: i) {
//            if (j != nullptr) {
//                target.draw(*(j->get_vertices()), states);
//            }
//        }
//    }
}
