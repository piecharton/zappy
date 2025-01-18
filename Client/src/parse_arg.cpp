#include "header.h"
#include <iostream>
#include <unistd.h>  // for getopt
#include <cstring>   // for strlen
#include <string>    // needed for std::string

std::ostream &operator<<(std::ostream &out, const struct client_config &obj)
{
    return out << "Client will connect to port " << obj.port << std::endl
               << "Client team is  " << obj.team_name << std::endl
               << "Server hostname is  " << obj.hostname << std::endl;
}

struct client_config argument_parsing(int argc, char *argv[])
{
    int opt;
    struct client_config config;

    while ((opt = getopt(argc, argv, "h:n:p:")) != -1)
    {
        try
        {
            switch (opt)
            {
            // only numbers
            case 'p':
                config.port = std::stoi(std::string(optarg, strlen(optarg)));
                break;
            case 'n':
                config.team_name = std::string(optarg, strlen(optarg));
                break;
            case 'h':
                config.hostname = std::string(optarg, strlen(optarg));
                break;
            case '?':
            default:
                std::cout << "Unknown option:" << optopt << std::endl;
                break;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Exception caught : " << e.what() << '\n';
            config.validity = false;
        }
    }

    std::cout << config;
    return config;
}
