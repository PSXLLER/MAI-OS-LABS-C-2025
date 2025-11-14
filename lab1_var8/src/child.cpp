#include "os_wrapper.h"
#include "common.h"
#include <cstdlib>
#include <cstring>

int main() 
{
    FILE* f = os_open_file("input.txt", "r");
    if (!f) 
    {
        os_print("Error: cannot open input.txt\n");
        os_exit(1);
    }

    char line[MAX_LINE];
    while (os_read_line(f, line, sizeof(line))) 
    {
        int nums[MAX_NUMS];
        int count = 0;

        char* token = strtok(line, " \t\n");
        while (token && count < MAX_NUMS) 
        {
            nums[count++] = atoi(token);
            token = strtok(NULL, " \t\n");
        }
        if (count == 0) 
        {
            continue;
        }

        int result = nums[0];
        int div_by_zero = 0;

        for (int i = 1; i < count; ++i) 
        {
            if (nums[i] == 0) 
            {
                div_by_zero = 1;
                break;
            }
            result /= nums[i];
        }

        if (div_by_zero) 
        {
            os_print("Division by zero detected. Terminating.\n");
            os_close_file(f);
            os_exit(0);
        }

        char out[128];
        sprintf(out, "Result: %d\n", result);
        os_print(out);
    }

    os_close_file(f);
    os_exit(0);
}
