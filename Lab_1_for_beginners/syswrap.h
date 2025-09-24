#pragma once
#define SYSWRAP_H

int my_pipe(int fds[2]);
int my_fork(void);
int my_dup2(int oldfd, int newfd);
int my_execl(const char *path);
int my_wait(int pid, int *status);

