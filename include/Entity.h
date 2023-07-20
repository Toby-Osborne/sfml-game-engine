#ifndef CPPGAME_TEST_ENTITY_H
#define CPPGAME_TEST_ENTITY_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "EngineDefines.h"

class Entity {
    // This is the class that exists as not-tiles
    // Therefore needs to implement everything that isn't a tile in this class?
    // Everything should have a hitbox maybe?  Probably should be hidden away
    // All hitboxes will be rectangles drawn around the com.

public:
    typedef struct hitbox {
        float _x_negative_bound;
        float _y_negative_bound;
        float _x_positive_bound;
        float _y_positive_bound;
    } hitbox;

    [[nodiscard]] const sf::Vector2f &get_entity_coordinates() const {
        return _entity_coordinates;
    }

    void set_entity_coordinates(const sf::Vector2f &entityCoordinates) {
        _entity_coordinates = entityCoordinates;
    }

    // TODO: Implement collision physics
    bool is_colliding_x_pos();

    bool is_colliding_y_pos();

    bool is_colliding_x_neg();

    bool is_colliding_y_neg();

    Entity(Map *map, hitbox entity_hitbox, sf::Vector2f spawn_pos);

private:
    sf::Vector2f _entity_coordinates;
    sf::Vector2i _entity_tile_coordinates;
    hitbox _this_hitbox{};
    Map *_map;

    static bool _tile_is_passable(uint8_t tile_id);

    // Should all entities have physics?
};

#endif //CPPGAME_TEST_ENTITY_H
