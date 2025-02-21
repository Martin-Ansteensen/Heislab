#include <time.h>
#include "timer.h"


static time_t start_time;


void timer_start() {
    start_time = 0;
    start_time=clock();
}
double timer_get() {
    time_t current_time = clock();
    double elapsed_time = ((double)(current_time - start_time)) / CLOCKS_PER_SEC;
    return elapsed_time;
}

