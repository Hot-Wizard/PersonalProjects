/*TODO make error control*/
/*TODO make it as a struct or class*/
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>

int main()
{
    //creates the server socket     
    int serverSocket = socket(AF_INET/*IPv4*/, SOCK_STREAM/*TCP*/, 0);

    sockaddr_in serverAdrr;//Stores the addres of the socket
    serverAdrr.sin_family = AF_INET;
    serverAdrr.sin_port = htons(8080);//converts ports to byte
    serverAdrr.sin_addr.s_addr = INADDR_ANY;//Listen to all avalabes IP's
    
    //bind socket to address
    bind(serverSocket, (struct sockaddr*) &serverAdrr, sizeof(serverAdrr));

    //listen for Incoming Connections
    listen(serverSocket, 5);

    //reads the clientSocket
    int clientSocket = accept(serverSocket, nullptr, nullptr);

    /*///RECEIVE DATA FROM CLIENT///*/
    char buffer[1024] = {0};
    std::string message;
    int bytesReceived;
    while(1)
    {
        memset(buffer, 0, sizeof(buffer));
        std::cout<<"Waiting message from client\n";

        bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if(bytesReceived <= 0)
        {
            std::cout<<"Client Disconnected\n";
            break;
        }

        buffer[bytesReceived] = '\0';
        std::cout<<"Message received\n";
            
        if ((std::string)buffer == "exit") break;
        std::cout << "Client message: "<<buffer << "\n";
        std::getline(std::cin, message);

        if (message == "exit") {
            send(clientSocket, message.c_str(), message.length(), 0);
            break;
        }
        send(clientSocket, message.c_str(), message.length(), 0);
        std::cout<<"Message sent\n";
        
    }
    memset(buffer, 0, sizeof(buffer));

    //close
    close(clientSocket);
    close(serverSocket);

    return 0;

}