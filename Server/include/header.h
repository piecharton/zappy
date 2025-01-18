#ifndef ZAPPY_SERVER_HEADER_H
#define ZAPPY_SERVER_HEADER_H

#include "generate_map.h"

struct game_config
{
    bool validity = true;
    int port = 0;
    int width = 100;
    int height = 100;
    int time = 1;
    std::vector<std::string> team_names{"Blazing pandas",
                                        "Fruity postcards"};
    int clients = 0;
};

std::ostream &operator<<(std::ostream &out, const struct game_config &obj);
struct game_config argument_parsing(int argc, char *argv[]);

#endif // ZAPPY_SERVER_HEADER_H 
