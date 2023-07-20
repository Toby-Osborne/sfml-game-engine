#include "Entity.h"

Entity::Entity(Map *map, hitbox entity_hitbox, sf::Vector2f spawn_pos) {
    _map = map;
    _this_hitbox = entity_hitbox;
    _entity_coordinates = spawn_pos;
}

int fast_round_32(int num) {
    return (num + 15) & -16;
};

bool Entity::is_colliding_y_neg() {

}

bool Entity::is_colliding_y_pos() {
    int pixel_pos = (int) (_this_hitbox._y_positive_bound + _entity_coordinates.x);
    int closest_downwards_tile = fast_round_32(pixel_pos);
    if (closest_downwards_tile - pixel_pos < 2) return true;
    return false;
}

bool Entity::_tile_is_passable(uint8_t tile_id) {
    switch (tile_id) {
        case 0:
            return true;
        default:
            return false;
    };
}