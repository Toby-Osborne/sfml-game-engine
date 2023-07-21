#ifndef CPPGAME_TEST_PLAYER_H
#define CPPGAME_TEST_PLAYER_H

#include <SFML/Graphics.hpp>
#include "ChunkHandler.h"
#include "Entity.h"

class Player : public Entity, public sf::Drawable {
public:
    [[nodiscard]] const sf::Vector2f &get_player_coordinates() const {
        return Entity::get_entity_coordinates();
    }

    Player(Map *map, sf::Vector2f spawn_pos);  // Map loaded on launch

    void process_entity() override;

    void process_player_input(const sf::Vector2f &joystick);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    Map *_map;
    sf::Clock _player_clock;

    // Scuffed Physics implementation?
    // This all is in tiles per second
    float mass = 1.0;
    float gravity = 9.81;
    float inverse_mass = 1.f / mass;
    float acceleration_coefficient = 10.f * gravity; // "g's"

    float max_velocity = 32.f;  // Tiles per second
    float jump_velocity = 16.f; // Tiles per second
    sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);
    static constexpr float vel_stop_threshold = 10.f; // automatic stop velocity

    sf::Vector2f _joystick = sf::Vector2f(0, 0);

    void _handle_player_physics(const sf::Vector2f &movement_input);

    static constexpr Entity::hitbox default_player_hitbox = {16.f, 16.f, 16.f, 16.f};
};


#endif //CPPGAME_TEST_PLAYER_H
