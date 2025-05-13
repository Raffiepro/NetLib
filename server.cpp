#include "netlib.hpp"
#include <iostream>
#include <string.h>

int main()
{
    //TCPServer s(8080);
    UDPServer u(8080);
    u.setBlocking(false);

    //s.accept();

    char buff[1024];
    memset(buff,0,1024);

    while (true)
    {
        if(u.recv(0,(void*)buff,1024)>0) {
            std::cout<<buff<<'\n';
            memset(buff,0,1024);
        }
    }

    //std::cout<<std::hex<<buff<<'\n';
    /*std::string input;
    char buffer[1024] = { 0 };
    while(true) {
        std::cout<<s.recv(0, buffer, sizeof(buffer))<<'\n';
        std::cout << buffer << std::endl;
        memset(buffer,0,1024);
        
        std::getline(std::cin, input);
        s.send(0,input.c_str(),input.length());
    }*/

    u.stop();
    return 0;
}