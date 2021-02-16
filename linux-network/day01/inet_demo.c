
#include <stdio.h>
#include <arpa/inet.h>

int main() {
//    char *ipv4 = "192.168.1.1";
//    char *ipv4 = "localhost";
    char *ipv4 = "127.0.0.1";
    struct in_addr ip4;
    inet_pton(AF_INET, ipv4, &ip4);
//    printf("%x\n", ip4.s_addr);

    struct sockaddr_in server_addr;
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr.s_addr);
    server_addr.sin_port = 5433;
    printf("ip:port = %u:%d\n", server_addr.sin_addr.s_addr, server_addr.sin_port);
    return 0;
}