#include "Map.h"
#include "EngineDefines.h"
#include <fstream>
#include <sys/stat.h>

inline bool file_exists(const std::string &name) {
    struct stat buffer{};
    return (stat(name.c_str(), &buffer) == 0);
}

Map::Map(std::string map_name) {
    this->_map_name = map_name;
    map_name = "saves/" + map_name + ".nig";

    if (file_exists(map_name)) {
        char map_header[8];
        std::fstream fin(map_name, std::fstream::in);
        for (char &i: map_header) {
            fin >> std::noskipws >> i;
        }
        this->_map_width = ((uint32_t *) map_header)[0];
        this->_map_height = ((uint32_t *) map_header)[1];
        this->_map_data = new uint8_t[_map_width * _map_height];
        for (uint32_t i = 0; i < _map_width * _map_height; i++) {
            fin >> std::noskipws >> _map_data[i];
        }
    } else {
        // Need to make an actual GUI for this
        make_new(1000 * 16, 500 * 16);
    }
}

void Map::make_new(uint32_t map_width, uint32_t map_height) {
    this->_map_width = map_width;
    this->_map_height = map_height;
    this->_map_data = new uint8_t[_map_width * _map_height];
    for (uint32_t i = 0; i < _map_width * _map_height; i++) {
        _map_data[i] = 0;
    }
}

// The first 8 Bytes of a .nig file is the map header, containing the width and height of the map.
void Map::save_map() {
    std::ofstream save_file;
    std::string map_name = "saves/" + _map_name + ".nig";
    save_file.open(map_name);
    uint32_t header[2];
    header[0] = _map_width;
    header[1] = _map_height;
    save_file.write((char *) header, sizeof(int) * 2);
    save_file.close();
    save_file.open(map_name, std::ios_base::app);
    save_file.write((const char *) _map_data, _map_width * _map_height * sizeof(char));
}

void Map::update_map(unsigned int x, unsigned int y, unsigned int tile_id) {
    _map_data[x + y * _map_width] = tile_id;
}


Map::~Map() {
    save_map();
    delete _map_data;
}