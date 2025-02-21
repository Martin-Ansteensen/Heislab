#include "fsm.h"
#include "que.h"

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

void fsm_take_orders(fsm* fsm) {
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){

            int btnPressed = elevio_callButton(f, b);
            elevio_buttonLamp(f, b, btnPressed);

            if(btnPressed) {
                if(b==BUTTON_HALL_DOWN) {
                    MotorDirection trip_dir = DIRN_DOWN;
                    que_add_node_back(fsm->head, f, trip_dir);
                } else if(b==BUTTON_HALL_UP) {
                    MotorDirection trip_dir = DIRN_UP;
                    que_add_node_back(fsm->head, f, trip_dir);
                } else if(b=BUTTON_CAB) {
                    MotorDirection trip_dir = DIRN_STOP;
                    que_add_node_back(fsm->head, f, trip_dir);
                }
            }   
        }
    }
}


void fsm_execute_state_function(fsm* fsm) {
    if (fsm->state == IDLE) {
        fsm_idle(fsm);
    } else if (fsm->state == WAITING) {
        fsm_waiting(fsm);
    } else if (fsm->state == MOVING) {
        fsm_moving(fsm);
    } else if (fsm->state == REACHED_FLOOR) {
        fsm_reached_floor(fsm);
    } 
}

