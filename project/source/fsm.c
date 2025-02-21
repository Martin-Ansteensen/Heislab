#include "fsm.h"

void fsm_init() {
    int current_floor = elevio_floorSensor();

    //If elevator is not on designated floor, it will move up until it reaches a floor
    if(current_floor==-1) {
        elevio_motorDirection(DIRN_UP);
        
        while(current_floor==-1) { 
        }
        elevio_motorDirection(DIRN_STOP);
    } 
}
