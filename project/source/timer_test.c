#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

int main() {
    for(int j=0; j<10;j++) {

    
    timer_start();
    for(int i = 0; i<1000000000; i++) {

    }
    printf("%f\n", timer_get());
    }
    return 0;
}