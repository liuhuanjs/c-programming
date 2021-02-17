/*
 * Requirements:
 *      Verify wheather global variables can be shared between parent progress
 *      and child progree.
 * Conlusion:
 *      Can not share global variables. Write copy, Read share.
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int g_var = 11;

int main() {
    /* creates child progress */
    pid_t pid = fork();
    if (pid < 0)     // fork error
    {
        perror("fork error");
        return 1;
    } else if (pid > 0) // parent process
    {
        printf("I'm parent pid = %d , fork a child pid = %d\n", getpid(), pid);
        g_var = g_var + 11;
        printf(" - parent's g_var = %d\n", g_var);
        sleep(60);
    } else if (pid == 0)// child process
    {
        sleep(2); /* to void child process finished when parent process running */
        printf("I'm child  pid = %d, my parent pid = %d\n", getpid(), getppid());
        printf(" - child's  g_var = %d\n", g_var);
        sleep(60);
    }
    return 0;
}