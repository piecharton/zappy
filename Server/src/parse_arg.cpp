#include "header.h"

// DONE Parse arguments into structure
// TODO Map generation with food and minerals

#include <iostream>
#include <unistd.h>
#include <cstring>

std::ostream &operator<<(std::ostream &out, const struct game_config &obj)
{
    std::string team_names;
    for (const std::string &name : obj.team_names)
    {
        team_names.append("\t");
        team_names.append(name);
        team_names.append("\n");
    }

    return out << "Server will listen to port " << obj.port << std::endl
               << "Game width set to " << obj.width << std::endl
               << "Game height set to " << obj.height << std::endl
               << "Number of clients required to start the game " << obj.clients << std::endl
               << "Game time unit is 1/" << obj.time << std::endl
               << "Teams are " << std::endl
               << team_names;
}

struct game_config argument_parsing(int argc, char *argv[])
{
    int opt;
    std::vector<std::string> team_names;

    struct game_config config;

    while ((opt = getopt(argc, argv, "p:x:y:n:c:t:")) != -1)
    {
        try
        {
            switch (opt)
            {
            // only numbers
            case 'p':
                config.port = std::stoi(std::string(optarg, strlen(optarg)));
                break;
            case 'x':
                config.width = std::stoi(std::string(optarg, strlen(optarg)));
                break;
            case 'y':
                config.height = std::stoi(std::string(optarg, strlen(optarg)));
                break;
            case 'c':
                config.clients = std::stoi(std::string(optarg, strlen(optarg)));
                break;
            case 't':
                config.time = std::stoi(std::string(optarg, strlen(optarg)));
                break;
            case 'n':
            {
                // team names parsing
                config.team_names.clear();
                config.team_names.push_back(std::string(optarg, strlen(optarg)));

                for (int i = optind; (i < argc) && (argv[i][0] != '-'); ++i)
                {
                    config.team_names.push_back(std::string(argv[i], strlen(argv[i])));
                }
            }
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
