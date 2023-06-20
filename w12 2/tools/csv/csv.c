#include "csv.h"
#define CELL_LEN 2048

csv_file* csv_append(char* name, size_t line_len) {
    csv_file* file = malloc(sizeof(csv_file));
    file->csv_file = fopen(name, "a+");
    file->line_len = line_len;

    return file;
}

csv_file* csv_create(char* name, size_t header_len, char** header) {
    csv_file* file = malloc(sizeof(csv_file));
    file->csv_file = fopen(name, "w+");
    file->line_len = header_len;

    csv_add_line(file, header);

    return file;
}

void csv_add_line(csv_file* file, char** line) {
    size_t line_len = file->line_len;

    char line_str[CELL_LEN * line_len];
    line_str[0] = '\0';
    strncpy(line_str, line[0], CELL_LEN);
    for(size_t i = 1; i < line_len; ++i) {
        strncat(line_str, ",", CELL_LEN);
        strncat(line_str, line[i], CELL_LEN);
    }

    fprintf(file->csv_file, "%s\n", line_str);
}

void csv_close(csv_file* file) {
    fclose(file->csv_file);
    free(file);
}
