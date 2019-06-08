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

/**
 * @brief Esta función se encarga de convertir imagenes a base64 para poder
 * enviar los datos mediante el servidor, en "path" se debe escojer el path de acuerdo a la maquina
 * donde se estè usando.
 * @return
 */
string Client::encodeimage() {
    const char *path = "/home/dantroll/CLionProjects/ClientTest/prueba.jpg";
    FILE* file = fopen(path,"rb");
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

/**
 * @brief Esta es la funciòn encargada de levantar el servidor, cada vez que termina una conexiòn queda esperando
 * por màs.
 * *El problema es que el string que se recibe del cliente solo parece tener 33 caracteres, y aun no se como
 * solucionarlo.
 * @return
 */

int Client::server_connect() {
    /**
     * Esto solo es para inicializar correctamente la conexiòn y
     * definir puerto e ip.
     */
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
    /*************************************************

    /**
     * Crea el nuevo socket con el que se va a comunicar con el server.
     */
    int connectRes = connect(sock, (sockaddr *) &hint, sizeof(hint));
    if (connectRes == -1) {
        return 1;
    }

    char buf[4096];


    string mensajeCliente = encodeimage();
    std::cout << mensajeCliente << std::endl;

    /**
     * Aquì es donde se envìa al servidor la informaciòn, en este caso son los bytes de una
     * imagen en base64.
     */
    int sendRes = send(sock, mensajeCliente.c_str() , sizeof(mensajeCliente) + 1, 0);
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


