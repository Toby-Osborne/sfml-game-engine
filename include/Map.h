#ifndef CPPGAME_TEST_MAP_H
#define CPPGAME_TEST_MAP_H

#include <string>
#include <memory>

class Map {
public:
    Map(std::string map_name);
    Map(std::string map_name,uint32_t map_width,uint32_t map_height);
    int map_width() const { return _map_width; }
    int map_height() const { return _map_height; }
    uint8_t *map_data() const { return _map_data; }
    void save_map();
    ~Map();
private:
    std::string _map_name;
    uint8_t *_map_data;
    int _map_width;
    int _map_height;
};


#endif //CPPGAME_TEST_MAP_H
