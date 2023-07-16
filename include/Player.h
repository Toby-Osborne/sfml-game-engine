#ifndef CPPGAME_TEST_PLAYER_H
#define CPPGAME_TEST_PLAYER_H

#include <SFML/Graphics.hpp>
#include <MapRender.h>
class Player {
public:
    const sf::Vector2f get_player_coordinates();
    explicit Player(std::shared_ptr<Map> map);  // Map loaded on launch

    // This is a terrible solution because if player goes out of scope then its over
    MapRender *get_map();

    void process_player();
private:
    sf::Vector2f _player_coordinates = sf::Vector2f(320,320);
    std::unique_ptr<MapRender> _render_map;
    std::shared_ptr<Map> _map;
};


#endif //CPPGAME_TEST_PLAYER_H
