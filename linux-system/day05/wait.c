/*
 * wait(): Recycles child process by parent process.
 *
 * Note:
 *      use command ` ps aux | grep 'wait' ` to find the process
 *      status when runing this case.
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

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

        /* recycles child process */
        int status;
        pid_t wpid = wait(&status);
        printf(" - parent's wpid = %d\n", wpid);
        if(WIFEXITED(status))        // normal exit
        {
            printf("child normal exit, status = %d\n", WEXITSTATUS(status));
        }
        else if(WIFSIGNALED(status)) // exit if signaled
        {
            printf("child killed by signal, signo = %d\n", WTERMSIG(status));
        }

        sleep(60);
    } else if (pid == 0) // child process
    {
        sleep(2);
        printf("I'm child  pid = %d, my parent pid = %d\n", getpid(), getppid());
        printf(" - child's  g_var = %d\n", g_var);
        sleep(30);
    }
    return 0;
}