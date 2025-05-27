#include "mininet.hpp"
#include <iostream>
#include <string.h>

int main()
{
    UDPServer s(8080);
    //s.accept();

    char buffer[1024] = { 0 };

    sockaddr_in client;
    while(true) {
        memset(buffer,0,1024);

        size_t rs = s.recv(&client, buffer, sizeof(buffer));

        std::cout << rs << '\n'; //PRINTS SIZE
        std::cout << buffer << std::endl; //PRINT RECIEVED DATA

        s.send(&client, buffer, rs); //ECHO
    }

    s.stop();
    return 0;
}
