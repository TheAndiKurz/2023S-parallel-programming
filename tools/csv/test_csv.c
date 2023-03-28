#include "csv.h"

int main() {
    char* header[4] = { "Header 1", "Header 2", "Header 3", "Header 4" };
    char* line1[4] = { "100", "150", "200", "250" };
    char* line2[4] = { "200", "250", "300", "350" };

    csv_file* csv = csv_create("test.csv", 4, header);

    csv_add_line(csv, line1);
    csv_add_line(csv, line2);

    csv_close(csv);
}