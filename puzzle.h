//
// Created by Vlad Isan on 05/12/2023.
//

#ifndef PUZZLE_H
#define PUZZLE_H

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <ranges>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "fmt/core.h"

enum class Colour {
    RED,
    GREEN,
    BLUE
};

using GroupColours = std::unordered_map<Colour, int>;

const std::unordered_map<std::string, Colour> ColourMap{
    {"red", Colour::RED},
    {"green", Colour::GREEN},
    {"blue", Colour::BLUE}
};

struct Group {
    GroupColours group_colours;
};

struct Game {
    int id;
    std::vector<Group> groups;
};

int puzzle_sample_1(const std::string &base_file_path);

int puzzle_sample_2(const std::string &base_file_path);

int puzzle_1(const std::string &base_file_path);

int puzzle_2(const std::string &base_file_path);

int do_puzzle_1(std::ifstream &file);

int do_puzzle_2(std::ifstream &file);

Game parse_game(const std::string &game_line);

int total_games_possible(const std::vector<Game> &games, const GroupColours &map);

int get_power_sum(const std::vector<Game> &games);

int get_game_power(const Game &game);

#endif //PUZZLE_H
