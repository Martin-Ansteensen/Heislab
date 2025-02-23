#include <stdio.h>
#include <stdlib.h>

#include "fsm.h"
#include "que.h"
#include "timer.h"



void fsm_init(fsm* fsm) {
    // If elevator is not on designated floor, it will move up until it reaches a floor
    elevio_motorDirection(DIRN_STOP);
    if(elevio_floorSensor() == -1)
    {
        elevio_motorDirection(DIRN_DOWN);
        while (elevio_floorSensor() == -1);
        elevio_motorDirection(DIRN_STOP);
    }
    fsm->floor = elevio_floorSensor();
    fsm->state = RESTING;
    printf("Reached valid floor: %i\n", elevio_floorSensor());
    elevio_floorIndicator(elevio_floorSensor());
    elevio_doorOpenLamp(0);
    for(int i = 0; i<N_FLOORS; i++) {
        elevio_buttonLamp(i, BUTTON_CAB, 0);
        elevio_buttonLamp(i, BUTTON_HALL_DOWN, 0);
        elevio_buttonLamp(i, BUTTON_HALL_UP, 0);
    }
}

void fsm_take_orders(fsm* fsm) {
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){

            int btnPressed = elevio_callButton(f, b);
            if(btnPressed) {
                elevio_buttonLamp(f, b, 1);
                if(b==BUTTON_HALL_DOWN) {
                    MotorDirection trip_dir = DIRN_DOWN;
                    que_add_node_back(fsm->head, f, trip_dir);
                } else if(b==BUTTON_HALL_UP) {
                    MotorDirection trip_dir = DIRN_UP;
                    que_add_node_back(fsm->head, f, trip_dir);
                } else if(b==BUTTON_CAB) {
                    MotorDirection trip_dir = DIRN_STOP;
        elevio_stopLamp(elevio_stopButton());            que_add_node_back(fsm->head, f, trip_dir);
                }
            }   
        }
    }
}


void fsm_execute_state_function(fsm* fsm) {
    if (fsm->state == RESTING) {
        fsm_resting(fsm);
    } else if (fsm->state == MOVING) {
        fsm_moving(fsm);
    }
}

void fsm_expedite_orders_at_floor(fsm* fsm, int floor){

    elevio_doorOpenLamp(1);  // open door
    fsm->door_open = 1;
    timer_start();

    que_delete_orders_for_floor(fsm->head, fsm->floor);
    
    elevio_buttonLamp(floor, BUTTON_CAB, 0);
    elevio_buttonLamp(floor, BUTTON_HALL_DOWN, 0);
    elevio_buttonLamp(floor, BUTTON_HALL_UP, 0);
}



void fsm_resting(fsm* fsm){

    if (
        elevio_floorSensor() != -1 &&
        que_is_orders_in_dir(fsm->head, fsm->floor, DIRN_STOP)  // there are orders in the same floor
    ) {
        fsm_expedite_orders_at_floor(fsm, fsm->floor);
    }
    
    else if (
        que_is_orders_in_dir(fsm->head, fsm->floor, DIRN_UP) &&  // there are orders above us
        !fsm->door_open  // we are not waiting to close the door
    ) {
        // Start moving up
        fsm->state = MOVING;
        fsm->dir = DIRN_UP;
        elevio_motorDirection(DIRN_UP);
    }
    
    else if(
        que_is_orders_in_dir(fsm->head, fsm->floor, DIRN_DOWN) &&  // there are orders below us
        !fsm->door_open  // we are not waiting to close the door
    ) {
        // Start moving down
        fsm->state = MOVING;
        fsm->dir = DIRN_DOWN;
        elevio_motorDirection(DIRN_DOWN);
    }

    else if(
        fsm->door_open  // we are waiting to close the door
    ){
        if (timer_get() >= 3 && elevio_obstruction() == 0){
            fsm->door_open = 0;
            elevio_doorOpenLamp(0);  // close door
        } else if(elevio_obstruction() == 1) {
            timer_start();
        }
    }
}

void fsm_moving(fsm* fsm){

    // We want to update the floor sensor and the fsm's floor everytime
    // we pass a new floor
    if (elevio_floorSensor() != -1){
        fsm->floor = elevio_floorSensor();
        elevio_floorIndicator(fsm->floor);
    }
    
    // We stop driving if there are no more orders in the direction
    // we are driving
    if (elevio_floorSensor() != -1 &&
        !que_is_orders_in_dir(fsm->head, fsm->floor, fsm->dir)
    ) {
        elevio_motorDirection(DIRN_STOP);
        fsm->state = RESTING;
        fsm_expedite_orders_at_floor(fsm, fsm->floor);  
    }

    // We stop driving if we reached a floor where there is an order
    // in the direction we are driving, or a order without direction
    // (a order from inside the elevator)
    if (elevio_floorSensor() != -1 &&
        (que_is_orders_for_floor_in_dir(fsm->head, fsm->floor, fsm->dir) ||
        que_is_orders_for_floor_in_dir(fsm->head, fsm->floor, DIRN_STOP))
    ) {
        elevio_motorDirection(DIRN_STOP);
        fsm->state = RESTING;
        fsm_expedite_orders_at_floor(fsm, fsm->floor);
    }
}