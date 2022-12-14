//
// Created by Chandan on 05-Sep-22.
//

#include <string>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

class Client{
public:
    int connectToServer(string hostname, int port);

    void sendData(int sock, string data);

    string receivedData(int sock);

    void disconnectFromServer(int sock);
};
