/*
 * Zombie process:
 *      parent process is alive but child process has been finished,
 *      And parent process doesn't recycles child, then this child will
 *      be zombie process.
 *
 * Note:
 *      use command ` ps aux | grep 'zombie' ` to find the zombie process
 *      status when runing this case.
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
        printf("I'm child  pid = %d, my parent pid = %d\n", getpid(), getppid());
        printf(" - child's  g_var = %d\n", g_var);

        /* No recycles child process when parent process running , there will generate zombie */
    }
    return 0;
}