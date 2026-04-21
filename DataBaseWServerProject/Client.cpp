#include <cstring>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>

int main()
{
    // creates socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Specify Address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    //try to connect
    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    /*////SEND DATA////*/
    char buffer[1024] = {0};
    std::string message;
    int bytesReceived;
    while(1)
    {
        //memset(&message, 0, sizeof(message));
        std::getline(std::cin, message);
        if(message == "exit")
        {
            send(clientSocket, message.c_str(), message.length(), 0);
            break;
        }
        send(clientSocket, message.c_str(), message.length(), 0);
        std::cout<<"message sent\n";

        memset(&buffer, 0, sizeof(buffer));
        std::cout<<"Waiting message from server\n";

        
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if(bytesReceived > 0)buffer[bytesReceived]='\0';

        if(strcmp(buffer, "exit") == 0)break;
        std::cout<<"Server Message: "<<buffer<<"\n";
    }

    memset(buffer, 0, sizeof(buffer));
    // close
    close(clientSocket);

    return 0;
}
