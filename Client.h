//
// Created by dantroll on 08/06/19.
//

#ifndef CLIENT_MYINVLIB_CLIENT_H
#define CLIENT_MYINVLIB_CLIENT_H

#include <string.h>
#include <string>
using namespace std;
class Client {

public:
    size_t Send(int sockfd, const void *buf, size_t len, int flag);

    int server_connect();

    string encodeimage();

    void recibir();

    int recibirP();

    void recibirS();

    void enviar();

    //std::char buf[];
    int sock;
    bool turno;
    std::string userInput;

};


#endif //CLIENT_MYINVLIB_CLIENT_H
