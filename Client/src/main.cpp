// C++ program to illustrate the client application in the
// socket programming
#include "header.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>


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
