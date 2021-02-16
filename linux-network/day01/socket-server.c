/*
 * socket server
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
    // step 1: create socket for listening local port
    int lfd = socket(AF_INET, SOCK_STREAM, 0);

    // step 2: bind ip and port to fd
    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(6666);
//    server.sin_addr.s_addr = INADDR_ANY;
//    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int ret = bind(lfd, (struct sockaddr *) &server, sizeof(server));
    if (ret < 0) {
        perror("bind error");
        return -1;
    }

    // step 3: listen
    listen(lfd, 5);
    char sip[16];
    memset(&sip, 0x0, sizeof(sip));
    inet_ntop(AF_INET, &server.sin_addr.s_addr, sip, sizeof(sip));
    printf("Server listen %s:%d\n", sip, ntohs(server.sin_port));

    // step 4: accept client's connection
    struct sockaddr_in client;
    socklen_t clen = sizeof(client);
    printf("Ready for accept client's connection ...\n");
    int cfd = accept(lfd, (struct sockaddr *) &client, &clen);

    // get client's ip and port
    char cip[16];
    memset(&cip, 0x0, sizeof(cip));
    printf("Get a client's connection, %s:%d , sfd=%d , cfd=%d\n",
           inet_ntop(AF_INET, &client.sin_addr.s_addr, cip, sizeof(cip)),
           ntohs(client.sin_port),
           lfd, cfd);

    // step 5: loop for communicating with client
    int n;
    char read_buf[1024];
    char *send_msg = "Hello client,I'm server.";

    while (1) {
        // read data from client
        memset(read_buf, 0x0, sizeof(read_buf));
        n = read(cfd, &read_buf, sizeof(read_buf));
        if (n <= 0) {
            printf("There is an error when read data from client, n=%d .\n", n);
            break;
        }
        printf(" - client [%d]: %s\n", n, read_buf);

        // send data to client
        write(cfd, send_msg, strlen(send_msg));
    }

    // finally, close sfd and cfd
    close(lfd);
    close(cfd);
    return 0;
}