#include "Player.h"

Player::Player(std::shared_ptr<Map> map) {
    _map = std::move(map);
    _render_map = std::make_unique<MapRender>("assets/tileset.png", sf::Vector2u(32, 32), _map);
    _render_map->load(_player_coordinates);
}

MapRender *Player::get_map() {
    return _render_map.get();
}

void Player::process_player() {

}