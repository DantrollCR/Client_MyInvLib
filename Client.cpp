//
// Created by dantroll on 08/06/19.
//

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "Client.h"
#include "base64.h"
#include <vector> // for vector
#include <iterator> // for std::istream_iterator and std::ostream_iterator
#include <algorithm> // for std::copy
#include <fcntl.h>

using namespace std;

string Client::encodeimage() {
    const char *path = "/home/dantroll/CLionProjects/ClientTest/prueba.jpg";
    FILE* file = fopen(path,"rb");
//some error checking stuff
    fseek(file, 0, SEEK_END);
    long len=ftell(file);
    fseek(file, 0, SEEK_SET);
    char* content=(char *)malloc(len+1);
    memset(content,0,len+1);
    fread(content, len, 1, file);
    string test = base64_encode(reinterpret_cast<const unsigned char *>(content), len);
    std::cout << test << std::endl;
    delete content;
    delete file;
    return test;

}

int Client::server_connect() {
    //	Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        return 1;
    }
    auto sockfd = socket(PF_INET, SOCK_STREAM, 0);
    fcntl(sockfd, F_SETFL, O_NONBLOCK);

    //	Create a hint structure for the server we're connecting with
    int port = 6969;
    string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //	Connect to the server on the socket
    int connectRes = connect(sock, (sockaddr *) &hint, sizeof(hint));
    if (connectRes == -1) {
        return 1;
    }

    //	While loop:
    char buf[4096];
    string userInput;


    string mensajeCliente = "{\"ID10\":[591206,2,3,2,3,8,9,2,5],\"ID11\":[55241,6,6,4,1,7,4,9,5],\"ID14\":[236321,9,8,3,6,8,5,6,7]}";
    std::cout <<mensajeCliente <<std::endl;


    int sendRes = send(sock,mensajeCliente.c_str() , sizeof(mensajeCliente) + 1, 0);
    if (sendRes == -1) {
        cout << "Could not send to server! Whoops!\r\n";
    }




    //		Wait for response
    memset(buf, 0, 4096);
    int bytesReceived = recv(sock, buf, 4096, 0);
    if (bytesReceived == -1) {
        cout << "There was an error getting response from server\r\n";
    } else {
        //		Display response
        cout << "SERVER> " << string(buf, bytesReceived) << "\r\n";
        close(sock);
    }

}


