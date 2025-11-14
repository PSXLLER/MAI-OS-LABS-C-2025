#pragma once
#include <cstdio>
#include <cstddef>

FILE* os_open_file(const char* name, const char* mode);
void  os_close_file(FILE* f);
bool  os_read_line(FILE* f, char* buf, size_t size);

FILE* os_open_process(const char* cmd, const char* mode);
void  os_close_process(FILE* p);

void  os_print(const char* msg);
void  os_exit(int code);
