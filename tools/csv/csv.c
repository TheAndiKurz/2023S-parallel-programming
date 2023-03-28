#include "csv.h"
csv_file* csv_create(char* name, size_t header_len, char** header) {
    csv_file* file = malloc(sizeof(csv_file));
    file->csv_file = fopen(name, "w+");
    file->line_len = header_len;

    csv_add_line(file, header);

    return file;
}

void csv_add_line(csv_file* file, char** line) {
    size_t line_len = file->line_len;

    char line_str[1024] = { 0 };
    strcpy(line_str, line[0]);
    for(size_t i = 0; i < line_len; ++i) {
        strcat(line_str, ",");
        strcat(line_str, line[i]);
    }
    strcat(line_str, "\n");

    fprintf(file->csv_file, "%s", line_str);
}

void csv_close(csv_file* file) {
    fclose(file->csv_file);
    free(file);
}