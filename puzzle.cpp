//
// Created by Vlad Isan on 05/12/2023.
//

#include "puzzle.h"

int puzzle_sample_1(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-sample-1.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_1(file);
}

int puzzle_sample_2(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-sample-2.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_2(file);
}

int puzzle_1(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-1.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_1(file);
}

int puzzle_2(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-2.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_2(file);
}

int do_puzzle_1(std::ifstream &file) {
    std::string line;
    std::vector<Game> games{};

    while (std::getline(file, line)) {
        games.push_back(parse_game(line));
    }

    return total_games_possible(games, {
                                    {Colour::RED, 12},
                                    {Colour::GREEN, 13},
                                    {Colour::BLUE, 14},
                                });
}

int do_puzzle_2(std::ifstream &file) {
    std::string line;
    std::vector<Game> games{};

    while (std::getline(file, line)) {
        games.push_back(parse_game(line));
    }

    return get_power_sum(games);
}

Game parse_game(const std::string &game_line) {
    Game game{.id = 0};

    std::regex game_regex{R"(Game (\d+): (.*))"};
    std::smatch game_match;

    if (std::regex_search(game_line, game_match, game_regex)) {
        game.id = std::stoi(game_match[1]);


        std::string groups = game_match[2];
        std::regex group_split_regex{"; "};
        std::sregex_token_iterator iter{groups.begin(), groups.end(), group_split_regex, -1};
        std::sregex_token_iterator end;

        for (; iter != end; ++iter) {
            Group group{};

            std::string group_string = *iter;
            std::regex group_regex{"([\\d]+) (\\w+)"};
            auto group_iter_begin = std::sregex_iterator(group_string.begin(), group_string.end(), group_regex);
            std::sregex_iterator group_iter_end;

            for (std::sregex_iterator i = group_iter_begin; i != group_iter_end; ++i) {
                const std::smatch &match_colours = *i;

                int number = std::stoi(match_colours[1]);
                std::string colour = match_colours[2];

                group.group_colours.emplace(std::make_pair(ColourMap.at(colour), number));
            }

            game.groups.push_back(group);
        }
    }

    return game;
}

int total_games_possible(const std::vector<Game> &games, const GroupColours &map) {
    int total = 0;

    auto is_group_valid = [&](auto &group) {
        return std::ranges::all_of(group.group_colours, [&](const auto &pair) {
            return map.at(pair.first) >= pair.second;
        });
    };

    std::ranges::for_each(games, [&](const Game &game) {
        total += std::ranges::all_of(game.groups, is_group_valid) ? game.id : 0;
    });

    return total;
}

int get_power_sum(const std::vector<Game> &games) {
    return std::reduce(games.begin(), games.end(), 0, [&](int init, const Game &game) {
        return init + get_game_power(game);
    });
}

int get_game_power(const Game &game) {
    GroupColours min_colour_no = {
        {Colour::RED, 0},
        {Colour::GREEN, 0},
        {Colour::BLUE, 0}
    };

    for (auto &group: game.groups) {
        for (auto &colour: group.group_colours) {
            if (colour.second > min_colour_no[colour.first]) {
                min_colour_no[colour.first] = colour.second;
            }
        }
    }

    return std::reduce(min_colour_no.begin(), min_colour_no.end(), 1, [&](int init, auto &colour) {
        return init * colour.second;
    });
}
