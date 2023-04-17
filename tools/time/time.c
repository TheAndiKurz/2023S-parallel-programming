#include "time.h"

#include "../csv/csv.h"
#define CELL_LEN 64

void add_time(char* name, size_t threads, double time) {
    csv_file* csv;

    FILE* f = fopen("times.csv", "r");
    if(f == NULL) {
        char* header[3] = { "name", "threads", "time" };
        csv = csv_create("times.csv", 3, header);
    } else {
        fclose(f);
        csv = csv_append("times.csv", 3);
    }

    char* line[3];
    line[0] = malloc(CELL_LEN);
    snprintf(line[0], CELL_LEN, "%s", name);
    line[1] = malloc(CELL_LEN);
    snprintf(line[1], CELL_LEN, "%zu", threads);
    line[2] = malloc(CELL_LEN);
    snprintf(line[2], CELL_LEN, "%lf", time);

    csv_add_line(csv, line);

    free(line[0]);
    free(line[1]);
    free(line[2]);

    csv_close(csv);
}

void add_time_value(char* name, size_t threads, double time, double value) {
    csv_file* csv;

    FILE* f = fopen("times.csv", "r");
    if(f == NULL) {
        char* header[4] = { "name", "threads", "time", "value" };
        csv = csv_create("times.csv", 4, header);
    } else {
        fclose(f);
        csv = csv_append("times.csv", 4);
    }

    char* line[4];
    line[0] = malloc(CELL_LEN);
    snprintf(line[0], CELL_LEN, "%s", name);
    line[1] = malloc(CELL_LEN);
    snprintf(line[1], CELL_LEN, "%zu", threads);
    line[2] = malloc(CELL_LEN);
    snprintf(line[2], CELL_LEN, "%lf", time);
    line[3] = malloc(CELL_LEN);
    snprintf(line[3], CELL_LEN, "%lf", value);

    csv_add_line(csv, line);

    free(line[0]);
    free(line[1]);
    free(line[2]);
    free(line[3]);

    csv_close(csv);
}
