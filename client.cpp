#include "netlib.hpp"
#include <iostream>
#include <string.h>

int main()
{
    UDPClient c("127.0.0.1", 8080);

    while(true) {
        std::string i;
        std::getline(std::cin, i);
        c.send(i.c_str(), i.size());
    }

    /*std::string input;
    char buffer[1024] = { 0 };
    while(true) {
        std::getline(std::cin, input);
        c.send(input.c_str(),input.length());
        memset(buffer,0,1024);

        std::cout<<c.recv(buffer, sizeof(buffer))<<'\n';
        std::cout << buffer << std::endl;
    }*/

    c.stop();
    return 0;
}