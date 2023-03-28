#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct csv_file {
    size_t line_len;
    FILE* csv_file;
};
typedef struct csv_file csv_file;

csv_file* csv_create(char* name, size_t header_len, char** header);

csv_file* csv_append(char* name, size_t line_len);

void csv_add_line(csv_file* file, char** line);

void csv_close(csv_file* file);