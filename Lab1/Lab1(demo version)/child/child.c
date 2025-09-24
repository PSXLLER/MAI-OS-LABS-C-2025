#include <stdio.h>
#include <stdlib.h>

int main()
{
    int result;
    int next;

    while(scanf("%d", &result) == 1)
    {
        while(scanf("%d", &next) == 1)
        {
            if(next == 0)
            {
                fprintf(stderr, "Div by zero\n");
                return 2;
            }
            result /= next;

            int a = getchar();
            if(a == '\n' || a == EOF)
            {
                break;
            }
            ungetc(a, stdin);
        }
        printf("%d\n", result);
    }

    return 0;
}