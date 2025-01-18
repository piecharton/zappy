#ifndef CLIENT_HEADER_H
#define CLIENT_HEADER_H

#include <iostream>
#include <string>

struct client_config
{
    bool validity = true;
    int port = 0;
    std::string team_name;
    std::string hostname = "localhost";
};

std::ostream &operator<<(std::ostream &out, const struct client_config &obj);
struct client_config argument_parsing(int argc, char *argv[]);

#endif
