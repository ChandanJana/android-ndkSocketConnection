//
// Created by Chandan on 05-Sep-22.
//

#include "Client.h"

/**
 *
 * @param hostname
 * @param port
 * @return
 */
int Client::connectToServer(string hostname, int port) {
    int sockets = 0;
    struct sockaddr_in sockaddrIn;
    if ((sockets = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        return -1;
    }

    sockaddrIn.sin_family = AF_INET;
    sockaddrIn.sin_port = htons(port);

    if (inet_pton(AF_INET, hostname.c_str(), &sockaddrIn.sin_addr) <= 0) {
        return -1;
    }

    if (connect(sockets, (struct sockaddr *) &sockaddrIn, sizeof(sockaddrIn)) < 0){
        return  -1;
    }
    return sockets;
}

/**'
 *
 * @param sock
 */
void Client::disconnectFromServer(int sock) {
    close(sock);
}

/**
 *
 * @param sock
 * @return
 */
string Client::receivedData(int sock) {
    char buffer[1024] = {0};
    int data = read(sock, buffer, 1024);

    if (data != -1)
        return buffer;
    else
        return "Error";
}

/**
 *
 * @param sock
 * @param data
 */
void Client::sendData(int sock, string data) {
    send(sock, data.c_str(), sizeof(data), 0);
}

