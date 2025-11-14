#include "os_wrapper.h"
#include <cstdlib>

FILE* os_open_file(const char* name, const char* mode) 
{
    return fopen(name, mode);
}

void os_close_file(FILE* f) {
    if (f) 
    {
        fclose(f);
    }
}

bool os_read_line(FILE* f, char* buf, size_t size) 
{
    return fgets(buf, size, f) != nullptr;
}

FILE* os_open_process(const char* cmd, const char* mode) 
{
    return popen(cmd, mode);
}

void os_close_process(FILE* p) 
{
    if (p) 
    {
        pclose(p);
    }
}

void os_print(const char* msg) 
{
    printf("%s", msg);
}

void os_exit(int code) 
{
    exit(code);
}
