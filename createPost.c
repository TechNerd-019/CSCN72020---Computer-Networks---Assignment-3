#include "header.h"

void createPost(SOCKET socket) {
    char post[128];
    char content[64], author[32], topic[32];

    // Get post details from user
    printf("Enter post content: ");
    scanf("%63s", content);
    printf("Enter author name: ");
    scanf("%31s", author);
    printf("Enter post topic: ");
    scanf("%31s", topic);

    // Construct the post message
    snprintf(post, sizeof(post), "%s+%s+%s", content, author, topic);

    // Send the post message to the server
    send(socket, post, sizeof(post), 0);

    printf("Post created successfully!\n");
}