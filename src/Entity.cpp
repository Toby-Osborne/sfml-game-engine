#include "Entity.h"

Entity::Entity(Map *map, hitbox entity_hitbox, sf::Vector2f spawn_pos) {
    _map = map;
    _this_hitbox = entity_hitbox;
    _entity_coordinates = spawn_pos;
}