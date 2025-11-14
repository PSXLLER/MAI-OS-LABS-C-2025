#include "os_wrapper.h"
#include "common.h"
#include <cstring>

int main() 
{
    FILE* pipe = os_open_process("./child", "r");
    if (!pipe) 
    {
        os_print("Error: cannot start child process\n");
        os_exit(1);
    }

    char buffer[MAX_LINE];
    while (os_read_line(pipe, buffer, sizeof(buffer))) 
    {
        os_print(buffer);
        if (strstr(buffer, "Division by zero"))
        {
            break;
        }
    }

    os_close_process(pipe);
    os_print("Parent terminated.\n");
    os_exit(0);
}
