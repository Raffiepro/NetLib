#include "netlib.hpp"
#include <iostream>
#include <string.h>
char buffer[1024] = { 0 };
int main()
{
    UDPClient c("127.0.0.1", 8080);

    while(true) {
        std::string s;
        std::getline(std::cin, s);
        c.send(s.c_str(), s.size());

        memset(buffer,0,1024);
        std::cout << c.recv(buffer, 1024) << '\n';
        std::cout << buffer << '\n';
    }

    c.stop();
    return 0;
}