#include <unistd.h>

#include "elevio.h"

void elevator_init() {
    int current_floor = elevio_floorSensor();

    //If elevator is not on designated floor, it will move up until it reaches a floor
    if(current_floor==-1) {
        elevio_motorDirection(DIRN_UP);
        
        while(current_floor==-1) { 
        }
        elevio_motorDirection(DIRN_STOP);
    } 
}

int trip_direction(int floor, ButtonType button) {
    int current_floor = elevio_floorSensor();
    int called_floor = elevio_callButton(floor,button);
    
    if(current_floor>called_floor) {
        return -1;
    } else if (current_floor<called_floor) {
        return 1;
    } else {
        return 0;
    }
}
