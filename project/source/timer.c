#include <sys/time.h>
#include "timer.h"
#include <stdlib.h>

void timer_start() {
    gettimeofday(&start, NULL);
}
double timer_get() {
    long seconds, microseconds;
    double elapsed_time;

    gettimeofday(&end, NULL);
    
    seconds = end.tv_sec - start.tv_sec;
    microseconds = end.tv_usec - start.tv_usec;
    elapsed_time = seconds + microseconds*1e-6;

    return elapsed_time;
}

