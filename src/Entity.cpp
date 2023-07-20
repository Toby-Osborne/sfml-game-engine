#include "Entity.h"

Entity::Entity(Map *map, hitbox entity_hitbox, sf::Vector2f spawn_pos) {
    _map = map;
    _this_hitbox = entity_hitbox;
    _entity_coordinates = spawn_pos;
}


bool Entity::will_collide_y(float dy) {
    if (dy > 0) {
        if (_is_point_colliding((int) (_this_hitbox._x_positive_bound + _entity_coordinates.x) / TILE_SIZE,
                                (int) (_this_hitbox._y_positive_bound + _entity_coordinates.y + dy) / TILE_SIZE))
            return true;
        for (int i = (int) -_this_hitbox._x_negative_bound; i < _this_hitbox._x_positive_bound; i += TILE_SIZE) {
            if (_is_point_colliding((int) (i + _entity_coordinates.x) / TILE_SIZE,
                                    (int) (_this_hitbox._y_positive_bound + _entity_coordinates.y + dy) / TILE_SIZE))
                return true;
        }
        return false;
    } else {
        if (_is_point_colliding((int) (_this_hitbox._x_positive_bound + _entity_coordinates.x) / TILE_SIZE,
                                (int) (-_this_hitbox._y_negative_bound + _entity_coordinates.y + dy) / TILE_SIZE))
            return true;
        for (int i = (int) -_this_hitbox._x_negative_bound; i < _this_hitbox._x_positive_bound; i += TILE_SIZE) {
            if (_is_point_colliding((int) (i + _entity_coordinates.x) / TILE_SIZE,
                                    (int) (-_this_hitbox._y_positive_bound + _entity_coordinates.y + dy) / TILE_SIZE))
                return true;
        }
        return false;
    }

}

bool Entity::will_collide_x(float dx) {
    if (dx > 0) {
        if (_is_point_colliding((int) (_this_hitbox._x_positive_bound + _entity_coordinates.x + dx) / TILE_SIZE,
                                (int) (_this_hitbox._y_positive_bound + _entity_coordinates.y) / TILE_SIZE))
            return true;
        for (int i = (int) -_this_hitbox._y_negative_bound; i < _this_hitbox._y_positive_bound; i += TILE_SIZE) {
            if (_is_point_colliding((int) (_this_hitbox._x_positive_bound + _entity_coordinates.x + dx) / TILE_SIZE,
                                    (int) (i + _entity_coordinates.y) / TILE_SIZE))
                return true;
        }
        return false;
    } else {
        if (_is_point_colliding((int) (-_this_hitbox._x_negative_bound + _entity_coordinates.x + dx) / TILE_SIZE,
                                (int) (_this_hitbox._y_positive_bound + _entity_coordinates.y) / TILE_SIZE))
            return true;
        for (int i = (int) -_this_hitbox._y_negative_bound; i < _this_hitbox._y_positive_bound; i += TILE_SIZE) {
            if (_is_point_colliding((int) (-_this_hitbox._x_negative_bound + _entity_coordinates.x + dx) / TILE_SIZE,
                                    (int) (i + _entity_coordinates.y) / TILE_SIZE))
                return true;
        }
        return false;
    }
}

bool Entity::_is_point_colliding(int x, int y) {
    return !_tile_is_passable(_map->get_tile(x, y));
}

bool Entity::_tile_is_passable(uint8_t tile_id) {
    if (tile_id == 0) {
        return true;
    } else {
        return false;
    };
}