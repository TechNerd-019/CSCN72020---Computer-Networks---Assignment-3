#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define SERVER_IP "172.16.5.12"
#define PORT 8000
#define MAX_MESSAGE_SIZE 128




void createPost(SOCKET socket);
void viewPost(SOCKET socket);