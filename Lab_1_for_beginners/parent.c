#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "syswrap.h"


int main()
{
    char path[1024];
    
    printf("Enter the path to the file:");
    
    if(!fgets(path, sizeof(path), stdin))
    {
        fprintf(stderr, "Failed to read path!\n" );
        return 1;
    }

    int n = strlen(path);
    if (n > 0 && path[n-1] == '\n')
    {
        path[n-1] = '\0';
    }

    FILE *fin = fopen(path, "r");
    if (!fin)
    {
        fprintf(stderr, "Failed to open\n");
        return 1;
    }
    
    int pipefd[2];
    if (my_pipe(pipefd) != 0)
    {
        fprintf(stderr, "Error: pipe()\n");
        fclose(fin);
        return 1;
    }
    
    int pid = my_fork();
    if (pid == 0)
    {
        my_dup2(fileno(fin), 0);
        my_dup2(pipefd[1], 1);
        close(pipefd[0]);
        close(pipefd[1]);
        fclose(fin);
        my_execl("./child");
        _exit(127);
    }

    fclose(fin);
    close(pipefd[1]);

    FILE* pin = fdopen(pipefd[0], "r");
    char buf[4096];
    while (fgets(buf, sizeof(buf), pin))
    {
        fputs(buf, stdout);
    }
    
    fclose(pin);

    int st;
    my_wait(pid, &st);
    if(WIFEXITED(st))
    {
        return WEXITSTATUS(st);
    }
    else
    {
        return 1;
    }
}