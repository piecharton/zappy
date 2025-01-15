// C++ program to show the example of server application in
// socket programming
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <argp.h>
#include <vector>

// DONE Parse arguments into structure
// TODO Map generation with food and minerals

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

int main(int argc, char *argv[])
{
    struct game_config config = argument_parsing(argc, argv);
    if (config.validity)
    {
        std::cout << "config valid" << std::endl;
    }
    // creating socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying the address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // binding socket.
    bind(serverSocket, (struct sockaddr *)&serverAddress,
         sizeof(serverAddress));

    // listening to the assigned socket
    listen(serverSocket, 5);

    while (true)
    {
        // accepting connection request
        int clientSocket = accept(serverSocket, nullptr, nullptr);

        // recieving data
        char buffer[1024] = {0};
        recv(clientSocket, buffer, sizeof(buffer), 0);
        std::cout << "Message from client: " << buffer << std::endl;
    }

    // closing the socket.
    close(serverSocket);

    return 0;
}
