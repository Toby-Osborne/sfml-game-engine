#include "Player.h"

Player::Player(Map *map, sf::Vector2f spawn_pos) : Entity::Entity(map, default_player_hitbox, spawn_pos) {
    _map = map;
    _player_clock.restart();
}

inline static constexpr float sign(float val) { return val < 0 ? -1.0 : 1.0; }

void Player::_handle_player_physics(const sf::Vector2f &movement_input) {

    sf::Vector2f _player_coordinates = Entity::get_entity_coordinates();

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

    // Handle Collisions

    if (will_collide_x(velocity.x * dt)) {
        velocity.x = 0;
    } else {
        _player_coordinates.x += velocity.x * dt;
    }


    if (will_collide_y(velocity.y * dt)) {
        velocity.y = 0;
    } else {
        _player_coordinates.y += velocity.y * dt;
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
