// C++ program to show the example of server application in
// socket programming
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <argp.h>
#include <vector>

// TODO Parse arguments into structure

int main(int argc, char *argv[])
{
    int opt;
    std::vector<std::string> team_names;

    while ((opt = getopt(argc, argv, "p:x:y:n:c:t:")) != -1)
    {
        switch (opt)
        {
        case 'p':
        case 'x':
        case 'y':
        case 'c':
        case 't':
        {
            const std::string argument_option(optarg, strlen(optarg));
            std::cout << "option [" << static_cast<char>(opt) << "] with arg " << argument_option << std::endl;
        }
        break;
        case 'n':
        {
            //team names parsing
            team_names.push_back(std::string(optarg, strlen(optarg)));
                std::cout << team_names.back() << std::endl;

            for (int i = optind; (i < argc) && (argv[i][0] != '-'); ++i)
            {
                const std::string current_team_name(argv[i], strlen(argv[i]));
                team_names.push_back(current_team_name);
                std::cout << team_names.back() << std::endl;
            }
        }
        break;
        case '?':
        default:
            std::cout << "Unknown option:" << optopt << std::endl;
            break;
        }
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

    // while (true)
    // {
    //     // accepting connection request
    //     int clientSocket = accept(serverSocket, nullptr, nullptr);

    //     // recieving data
    //     char buffer[1024] = {0};
    //     recv(clientSocket, buffer, sizeof(buffer), 0);
    //     std::cout << "Message from client: " << buffer << std::endl;
    // }

    // closing the socket.
    close(serverSocket);

    return 0;
}
