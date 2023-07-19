#ifndef CPPGAME_TEST_PLAYER_H
#define CPPGAME_TEST_PLAYER_H

#include <SFML/Graphics.hpp>
#include <ChunkHandler.h>

class Player {
public:
    const sf::Vector2f get_player_coordinates();

    explicit Player(std::shared_ptr<Map> map);  // Map loaded on launch

    // This is a terrible solution because if player goes out of scope then its over
    ChunkHandler *get_render_map();

    void process_player(const sf::Vector2f &movement_input);

private:
    sf::Vector2f _player_coordinates = sf::Vector2f(2000, 2000);
    std::unique_ptr<ChunkHandler> _render_map;
    std::shared_ptr<Map> _map;
    sf::Clock _player_clock;


    // Scuffed Physics implementation?
    float mass = 1.0;
    float inverse_mass = 1 / mass;
    float acceleration_coefficient = 3000.0;
    float max_velocity = 1000;
    sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);
    static constexpr int vel_stop_threshold = 100.0;

    void _handle_player_physics(const sf::Vector2f &movement_input);
};


#endif //CPPGAME_TEST_PLAYER_H
