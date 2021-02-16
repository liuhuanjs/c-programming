/*
 * A muti-process server
 *      The parent process listen a port and fork a new child process to
 *      hangle the client's request. Parent process can monitor a child
 *      process by signal mechanism.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>

int main(){

}