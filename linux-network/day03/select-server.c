#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>

/*
 * select is a synchronous I/O multiplexing technology
 */

int main() {
    int lfd;
    struct sockaddr_in server_addr, client_addr;

    /* step 1: create socket and listen */
    lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd < 0) {
        perror("Create socket error !");
        return -1;
    }

    // set port muliplexing
    int optval = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));

    server_addr.sin_family = AF_INET;
    int ret;
    ret = bind(lfd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_in));
    if (ret < 0) {
        perror("Bind socket error !");
        return -1;
    }

    ret = listen(lfd, 5);
    if (ret < 0) {
        perror("Listen socket error !");
        return -1;
    }

    /* step 2: init fd_set */
    fd_set read_fds;
    FD_ZERO(&read_fds);

    // put listen fd into read fd set
    FD_SET(lfd,&read_fds);

    int connfd[FD_SETSIZE];      /* valid connection fd set */
    for (int i = 0; i < FD_SETSIZE; i++) {
        // -1 : fd is valid
        connfd[i] = -1;
    }

    /* step 3: loop for calling select() */
    while (1) {
        // select() will block if there is no chaning fd
        struct timeval tt={.tv_sec=10,.tv_usec=0};
        int n = select(lfd + 1, &read_fds, NULL, NULL, &tt);
        if (n > 0) {

        }
    }
}