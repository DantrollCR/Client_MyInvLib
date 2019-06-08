#include <iostream>

#include "Client.h"

using namespace std;

int main() {
    /*sudo apt-get install libboost-all-dev
    Poner eso en la terminal para que funcione ak7
    cada carpeta tiene un main propio donde solo se corre el .init
     */
    Client client;
    client.server_connect();
    return 0;
}
