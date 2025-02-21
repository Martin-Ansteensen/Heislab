#include "fsm.h"
#include <stdio.h>

void fsm_init(fsm* fsm) {
    //If elevator is not on designated floor, it will move up until it reaches a floor
    elevio_motorDirection(DIRN_STOP);
    if(elevio_floorSensor() == -1)
    {
        elevio_motorDirection(DIRN_DOWN);
        while (elevio_floorSensor() == -1);
        elevio_motorDirection(DIRN_STOP);
    }
    fsm->floor = elevio_floorSensor();
    fsm->state = IDLE;
    printf("Reached valid floor: %i\n", elevio_floorSensor());
    elevio_floorIndicator(elevio_floorSensor());

}
