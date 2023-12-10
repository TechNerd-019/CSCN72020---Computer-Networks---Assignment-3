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


#include "Authentication.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


bool authenticateClient(int connectionSocket)
{
  /*
  For this implementation, a default PIN is hardcoded into the 
  server as a string. It will then be compared to the string
  received from the client to perform authentication.
  */

   char authenticationPIN[32] = "6538";
   char receivedFromClient[32];

   // Appropriate message is sent according to the response from the client.
   char messageSuccess[64] = "PIN-accepted.";
   char messageRetry[128] = "Retry:";
   char messageFail[64] = "X";


   /*
   When a client sends a message, an error-checking method is implemented
   to avoid receiving empty messages, or incomplete messages from the client.

   Implementing these is a good practice.
   */
   int bytesRead = recv(connectionSocket, receivedFromClient, sizeof(receivedFromClient), 0);

   if (bytesRead == 0)
   {
    std::cout << "The message received by the client is either incomplete, or no message has been received." << std::endl;
    return;
   }

   int attemptCounter = 0;

   while (attemptCounter != 2)
   {
    // If the PIN received from the client does not match that expected by the server, a response is sent.
    if (receivedFromClient != authenticationPIN)
    {

       send(connectionSocket, messageRetry, sizeof(messageRetry), 0); 
       // The user only has 2 attempts to authenticate themselves.
       // If the client sends back the wrong PIN more than twice,
       // boolean value "false" will be returned, and the connection with the client
       // will be dropped.
       attemptCounter++;

    }
    else
    {
       send(connectionSocket, messageSuccess, sizeof(messageSuccess), 0);
       return true;
    }

   }

   // If the PIN is not entered properly within the allocated ammount of time,
   // the function returns false, and the client is dropped.
   return false;



  
}