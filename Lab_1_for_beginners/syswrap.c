#include "syswrap.h"
#include <unistd.h>
#include <sys/wait.h>

int my_pipe(int fds[2])
{
    return pipe(fds);
}

int my_fork(void)
{
    return fork();
}

int my_dup2(int oldfd, int newfd)
{
    return dup2(oldfd, newfd);
}

int my_execl(const char* path)
{
    return execl(path, path, (char*)NULL);
}

int my_wait(int pid, int* status)
{
    return waitpid(pid, status, 0);
}