// C++ program to illustrate the client application in the
// socket programming
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

struct client_config
{
    bool validity = true;
    int port = 0;
    std::string team_name;
    std::string hostname = "localhost";
};

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

int main(int argc, char *argv[])
{
    struct client_config config = argument_parsing(argc, argv);
    if (config.validity)
    {
        std::cout << "config valid" << std::endl;
    }
    // creating socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // sending connection request
    connect(clientSocket, (struct sockaddr *)&serverAddress,
            sizeof(serverAddress));

    // sending data
    std::string buffer;
    std::cin >> buffer;
    send(clientSocket, buffer.c_str(), buffer.size(), 0);

    // closing socket
    close(clientSocket);

    return 0;
}
