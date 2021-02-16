/*
 * socket client
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
    // step 1: create socket for communicating with server
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd < 0) {
        perror("Create socket error !");
        return -1;
    }

    // step 2: connect server
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(6666);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr);
    printf("Try to connect server 127.0.0.1:%d\n", server.sin_port);

    int ret = connect(cfd, (struct sockaddr *) &server, sizeof(server));
    if (ret < 0) {
        perror("Connect server error !");
        return -1;
    }

    printf("Connect server 127.0.0.1:%d successfully.\n", server.sin_port);

    // step 3: communicate with server
    int n;
    char read_buf[1024];
    char *send_msg = "Hi server, this is client.";

    while (1) {
        // send data to server
        write(cfd, send_msg, strlen(send_msg));

        // read data from server
        memset(read_buf, 0x0, sizeof(read_buf));
        n = read(cfd, &read_buf, sizeof(read_buf));
        if (n < 0) {
            printf("read error , is server has been closed ? n=%d\n", n);
            break;
        }
        printf(" - server [%d]: %s\n", n, read_buf);
        sleep(10);
    }

    // close cfd
    close(cfd);
    return 0;
}