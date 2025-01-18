// C++ program to show the example of server application in
// socket programming
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

#include "header.h"


int main(int argc, char *argv[])
{
    struct game_config config = argument_parsing(argc, argv);
    if (config.validity)
    {
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

        auto map = generateMap(config.width, config.height, 0.05, 0.5);
        printMap(map);

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
    }

    return 0;
}
