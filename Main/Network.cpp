#include "Network.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <iostream>
#include <curl/curl.h>


using namespace std;

bool dataSent(char* address, int port, char *messageStr){
    struct sockaddr_in server_info;
    char *message = messageStr;
    
    
    //Initializes the socket, SOCK_DGRAM makes it UDP as the transfer protocol
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == 0)
    {
        cout << "SOCK ERROR" << "\n";
        return -1;
    }
    
    //Information regarding the port & location to connect the socket
    server_info.sin_family = AF_INET;
    server_info.sin_addr.s_addr = inet_addr(address);
    server_info.sin_port = htons(port);
    
    //Attempts to connect the socket to the port & ip address
    int testing = connect(sock, (struct sockaddr *)&server_info, sizeof(server_info));
    if(testing == -1){
        cout << "FAILURE WITH CONNECTING" << "\n";
        return -1;
    }
    
    //Attempts to send the message using the connected socket
    testing = send(sock, message, (int)strlen(message), 0);

    if(testing == -1){
        cout << "FAILURE WITH SENDING" << "\n";
        return -1;
    }
    
    cout << "Terminal reached" << "\n";
    return true;
}
