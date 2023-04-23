#pragma once

#include <stdlib.h>

#define TIME_CELL_LEN 64

void add_time(char* name, size_t threads, double time);
void add_time_value(char* name, size_t threads, double time, double value);
