    #include "header.h"

    int main() {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            perror("WSAStartup failed");
            return 1;
        }

        SOCKET clientSocket;
        struct sockaddr_in serverAddr;

        // Create socket
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == INVALID_SOCKET) {
            perror("Error creating socket");
            WSACleanup();
            return 1;
        }

        // Initialize server address struct
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
        serverAddr.sin_port = htons(PORT);

        // Connect to server
        if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            perror("Error connecting to server");
            closesocket(clientSocket);
            WSACleanup();
            return 1;
        }

        printf("Connected to server\n");




        int authentication = FALSE;

        // Authentication


        while(!authentication)
        {

        char pin[5];
        printf("Enter PIN: ");
        scanf("%4s", pin);
        send(clientSocket, pin, sizeof(pin), 0);

        // Receive authentication response
        char response[16];
        recv(clientSocket, response, sizeof(response) - 1, 0);
        response[15] = '\0';

        if (strcmp(response, "PIN accepted") == 0) {
            printf("Authentication successful\n");
            authentication = TRUE;
        }
        else if (strcmp(response, "Retry:") == 0){
            printf("Please retry the pin.\n");

        }
        else {
            printf("Incorrect PIN. Exiting.\n");
            closesocket(clientSocket);
            WSACleanup();
            exit(EXIT_FAILURE);
        }
        }
        

        // Client menu loop
        while (1) {
            printf("Menu:\n");
            printf("1. Create a post\n");
            printf("2. View a post\n");
            printf("3. Exit connection\n");

            char choice[2];
            printf("Enter choice: ");
            while (scanf("%1s", choice) != 1 || (choice[0] != '1' && choice[0] != '2' && choice[0] != '3'))
            {
                printf("Please retry: \n");
            }

            send(clientSocket, choice, sizeof(choice), 0);

            if (strcmp(choice, "1") == 0) {
                // Create a post
                createPost(clientSocket);
            }
            else if (strcmp(choice, "2") == 0) {
                // View a post
                viewPost(clientSocket);
            }
            else if (strcmp(choice, "3") == 0) {
                // Exit connection
                closesocket(clientSocket);
                printf("Connection closed.\n");
                break;
            }
        }

        closesocket(clientSocket);
        WSACleanup();

        return 0;
    }



