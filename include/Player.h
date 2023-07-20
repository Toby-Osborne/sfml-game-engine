#ifndef CPPGAME_TEST_PLAYER_H
#define CPPGAME_TEST_PLAYER_H

#include <SFML/Graphics.hpp>
#include "ChunkHandler.h"
#include "Entity.h"

class Player : public Entity {
public:
    [[nodiscard]] const sf::Vector2f &get_player_coordinates() const {
        return Entity::get_entity_coordinates();
    }

    void set_player_coordinates(const sf::Vector2f &entityCoordinates) {
        Entity::set_entity_coordinates(entityCoordinates);
    }

    Player(Map *map, sf::Vector2f spawn_pos);  // Map loaded on launch

    void process_player(const sf::Vector2f &movement_input);

private:
    Map *_map;
    sf::Clock _player_clock;

    // Scuffed Physics implementation?
    float mass = 1.0;
    float inverse_mass = 1 / mass;
    float acceleration_coefficient = 3000.0;
    float max_velocity = 1000;
    sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);
    static constexpr int vel_stop_threshold = 100.0;

    void _handle_player_physics(const sf::Vector2f &movement_input);

    static constexpr Entity::hitbox default_player_hitbox = {16.f, 16.f, 16.f, 16.f};
};


#endif //CPPGAME_TEST_PLAYER_H
