#include "netlib.hpp"

int main()
{
    UDPClient c("127.0.0.1", 8080);
    c.send("Arigato senpai!", 15);
    c.stop();
    return 0;
}