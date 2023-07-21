#ifndef CPPGAME_TEST_ENTITY_H
#define CPPGAME_TEST_ENTITY_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "EngineDefines.h"

class Entity : public sf::Drawable {
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

    sf::Texture *_entity_texture_map;
    

    void draw(sf::RenderTarget &target, sf::RenderStates states);

    void set_entity_coordinates(const sf::Vector2f &entityCoordinates) {
        _entity_coordinates = entityCoordinates;
    }

    // TODO: Implement collision physics
    bool will_collide_x(float dx);

    bool will_collide_y(float dy);

    Entity(Map *map, hitbox entity_hitbox, sf::Vector2f spawn_pos);

    virtual void process_entity() = 0;

private:
    sf::Vector2f _entity_coordinates;
    hitbox _this_hitbox{};
    Map *_map;

    int _entity_id;
    static sf::VertexArray *_entity_quads;

    bool _is_point_colliding(int x, int y);

    static bool _tile_is_passable(uint8_t tile_id);

    // Should all entities have physics?
};

#endif //CPPGAME_TEST_ENTITY_H
