#include "netlib.hpp"
#include <iostream>
#include <string.h>

int main()
{
    TCPServer s(8080);
    s.accept();

    char buffer[1024] = { 0 };
    memset(buffer,0,1024);
    
    std::cout<<s.recv(0, buffer, sizeof(buffer))<<'\n'; //PRINTS SIZE
    std::cout << buffer << std::endl; //PRINT RECIEVED DATA

    s.stop();
    return 0;
}