# NetLib C++
The coolest networking library for _c++_
### Currently supports server/client for TCP/UDP - Unix and Windows support
### _UDP Support not yet added for Windows_
# Examples
Basic TCP
_Server_
```c++
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
```
_Client_
```c++
  #include "netlib.hpp"

  int main()
  {
      TCPClient c("127.0.0.1", 8080);
      c.send("Arigato senpai!", 15);
      c.stop();
      return 0;
  }
```
# Networking Memes :)
meow (this sneaky meow is added for readme structure reasons)
<br><br>
<img src="https://i.redd.it/4h7435e5qsxe1.jpeg" height="400">
<img src="https://i.redd.it/6ow9gs1v7dze1.jpeg" width="400">
