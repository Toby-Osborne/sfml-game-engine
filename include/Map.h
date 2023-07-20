#ifndef CPPGAME_TEST_MAP_H
#define CPPGAME_TEST_MAP_H

#include <string>
#include <memory>
#include "EngineDefines.h"

class Map {
public:
    explicit Map(std::string map_name);

    void make_new(uint32_t map_width, uint32_t map_height);

    [[nodiscard]] int map_width() const { return _map_width; }

    [[nodiscard]] int map_height() const { return _map_height; }

    [[nodiscard]] uint8_t *map_data() const { return _map_data; }

    void save_map();

    void update_map(unsigned int x, unsigned int y, unsigned int tile_id);

    uint8_t get_tile(unsigned int x, unsigned int y);

    ~Map();

private:
    std::string _map_name;
    uint8_t *_map_data;
    int _map_width;
    int _map_height;

    static const uint32_t default_map_width = MAP_WIDTH_IN_CHUNKS * CHUNK_SIZE_IN_TILES;
    static const uint32_t default_map_height = MAP_HEIGHT_IN_CHUNKS * CHUNK_SIZE_IN_TILES;
};


#endif //CPPGAME_TEST_MAP_H