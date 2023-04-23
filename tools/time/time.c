#include "time.h"

#include "../csv/csv.h"

csv_file* get_file() {
    char* csv_name = getenv("TIME_CSV_NAME");
    if(csv_name == NULL) {
        csv_name = "times.csv";
    }

    FILE* f = fopen(csv_name, "r");
    if(f == NULL) {
        char* header[3] = { "name", "threads", "time" };
        return csv_create(csv_name, 3, header);
    }

    fclose(f);
    return csv_append(csv_name, 3);
}

void add_time(char* name, size_t threads, double time) {
    csv_file* csv = get_file();

    char* line[3];
    line[0] = malloc(TIME_CELL_LEN);
    snprintf(line[0], TIME_CELL_LEN, "%s", name);
    line[1] = malloc(TIME_CELL_LEN);
    snprintf(line[1], TIME_CELL_LEN, "%zu", threads);
    line[2] = malloc(TIME_CELL_LEN);
    snprintf(line[2], TIME_CELL_LEN, "%lf", time);

    csv_add_line(csv, line);

    free(line[0]);
    free(line[1]);
    free(line[2]);

    csv_close(csv);
}

void add_time_value(char* name, size_t threads, double time, double value) {
    csv_file* csv = get_file();

    char* line[4];
    line[0] = malloc(TIME_CELL_LEN);
    snprintf(line[0], TIME_CELL_LEN, "%s", name);
    line[1] = malloc(TIME_CELL_LEN);
    snprintf(line[1], TIME_CELL_LEN, "%zu", threads);
    line[2] = malloc(TIME_CELL_LEN);
    snprintf(line[2], TIME_CELL_LEN, "%lf", time);
    line[3] = malloc(TIME_CELL_LEN);
    snprintf(line[3], TIME_CELL_LEN, "%lf", value);

    csv_add_line(csv, line);

    free(line[0]);
    free(line[1]);
    free(line[2]);
    free(line[3]);

    csv_close(csv);
}
