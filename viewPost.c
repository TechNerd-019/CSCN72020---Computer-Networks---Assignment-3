#include "header.h"


void viewPost(SOCKET socket) {
    char author[32];
    printf("Enter author name to view posts: ");
    scanf("%31s", author);

    // Send author name to the server
    send(socket, author, sizeof(author), 0);

    // Receive and display the list of posts from the server
    char postContent[1024];  // Adjust the size as needed
    char messages[1024];      // Adjust the size as needed
    recv(socket, postContent, sizeof(postContent) - 1, 0);
    postContent[sizeof(postContent) - 1] = '\0';
    recv(socket, messages, sizeof(messages) - 1, 0);
    messages[sizeof(messages) - 1] = '\0';

    printf("Available posts by %s:\n", author);

    // Tokenize the received postContent based on the '+' delimiter
    char* token = strtok(postContent, "+");
    int postNumber = 1;

    while (token != NULL) {
        printf("%d. %s\n", postNumber, token);
        token = strtok(NULL, "+");
        postNumber++;
    }

    // Ask the user to select a post
    int selectedPost;
    printf("Enter the number of the post you want to view: ");
    scanf("%d", &selectedPost);

    // Send the selected post number to the server
    send(socket, &selectedPost, sizeof(selectedPost), 0);

    // Receive and display the content and messages of the selected post
    char selectedPostContent[1024];  // Adjust the size as needed
    char selectedPostMessages[1024]; // Adjust the size as needed
    recv(socket, selectedPostContent, sizeof(selectedPostContent) - 1, 0);
    selectedPostContent[sizeof(selectedPostContent) - 1] = '\0';
    recv(socket, selectedPostMessages, sizeof(selectedPostMessages) - 1, 0);
    selectedPostMessages[sizeof(selectedPostMessages) - 1] = '\0';

    printf("Content of selected post:\n%s\n", selectedPostContent);

    // Tokenize and display the received messages based on the '+' delimiter
    token = strtok(selectedPostMessages, "+");
    int messageNumber = 1;

    while (token != NULL) {
        printf("Message %d: %s\n", messageNumber, token);
        token = strtok(NULL, "+");
        messageNumber++;
    }

    // Allow the user to add a message to the discussion post
    char newMessage[256];  // Adjust the size as needed
    printf("Add a new message to the discussion post:\n");
    scanf(" %[^\n]", newMessage);

    // Send the new message to the server
    send(socket, newMessage, sizeof(newMessage), 0);
}
