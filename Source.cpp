/*
* Name: Salah Salame
* Professor: Dr. Elliot Coleshill
* Date: Sunday, December 10, 2023
* Course: CSCN72020 - Computer Networks
* Assignment 3: Server-side development for forum application.
*
* Server code developed by Salah Salame, and Amro Belbeisi.
*
*/

// Additional libraries and dependencies included within these headers:
#include "Authentication.h"
#include "Post.h"
// Networking libraries:
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void)
{
    // First step is to create a socket. Up to here, no changes done from the TCP lab.

    int serverSocket;              // Using a datagram protocol (UDP) as per assignment specifications.
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == -1) 
    {
        std::cout << "ERROR: Failed to create ServerSocket" << std::endl;
        return 0;
    }

    // Next step is to bind the socket to a port the application can use to listen on for connections.

    sockaddr_in SvrAddr;
    SvrAddr.sin_family = AF_INET;
    SvrAddr.sin_addr.s_addr = INADDR_ANY;
    SvrAddr.sin_port = htons(27000);
    if (bind(serverSocket, (struct sockaddr *)&SvrAddr, sizeof(SvrAddr)) == -1)
    {
        close(serverSocket);
        std::cout << "ERROR: Failed to bind ServerSocket" << std::endl;
        return 0;
    }


    // Next step is to set the server on listen(), so that it may accept incoming connection requests:

    if (listen(serverSocket, 1) == -1) 
    {
    close(serverSocket);
    std::cout << "ERROR: listen failed to configure ServerSocket" << std::endl;
    return 0;
    }

    // Next step is to define a client socket.

    int connectionSocket;
    connectionSocket = -1;


    // Next step is to authenticate a client.
    /*
    Now that a socket exists and is bind to a port on the operating system, a client may begin
    requesting to connect to the server at that port.

    A client must provide the required credentials in order to connect. If the correct PIN is not supplied,
    the server rejects the connection, until the proper PIN is supplied.

    More information on specific implementation found on "Authentication.cpp"
    */

    // Code exits upon successful execution.

    bool authenticationStatus;

    authenticationStatus = authenticateClient(connectionSocket);

    // Depending on the boolean value returned by the function, the connection is dropped, and the server keeps
    // on listening, or the server may send and receive messages to the authenticated client.


    // A variable for controlling options from the client menu is initialized and defined:

    int clientChoice = 0;

    if (authenticationStatus == false)
    {
        close(connectionSocket);
    }

    else
    {
        switch(clientChoice)
        {
            case 1:
              receivedMessage(connectionSocket);
              break;
            case 2:
      
        }

    }
 
    return 0;
}