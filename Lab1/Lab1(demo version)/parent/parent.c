#include "stdio.h"
#include "string.h"
#include "sys/types.h"
#include "unistd.h"
#include "sys/wait.h"

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
    if (pipe(pipefd) != 0)
    {
        fprintf(stderr, "Error: pipe()\n");
        fclose(fin);
        return 1;
    }
    
    pid_t pid = fork();
    if (pid == 0)
    {
        dup2(fileno(fin), STDIN_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        fclose(fin);
        execl("./child/child", "child", (char*)NULL);
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
    waitpid(pid, &st, 0);
    if(WIFEXITED(st))
    {
        return WEXITSTATUS(st);
    }
    else
    {
        return 1;
    }
}