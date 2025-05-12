#include "netlib.hpp"
#include <iostream>
#include <string.h>

int main()
{
    TCPServer s(8080);
    s.accept();

    std::string input;
    char buffer[1024] = { 0 };
    while(true) {
        std::cout<<s.recv(0, buffer, sizeof(buffer))<<'\n';
        std::cout << buffer << std::endl;
        memset(buffer,0,1024);
        
        std::getline(std::cin, input);
        s.send(0,input.c_str(),input.length());
    }

    s.stop();
    return 0;
}