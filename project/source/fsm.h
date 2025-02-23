#pragma once
#include "que.h"
#include "driver/elevio.h"

typedef enum {
    UNDEFINED = -1,
    RESTING = 1,
    MOVING = 2
} States;

typedef struct {
    States state;
    MotorDirection dir;
    int door_open; // 1 for open, 0 for closed
    Node** head;
    int floor;
} fsm;

void fsm_init(fsm* fsm);

void fsm_take_orders(fsm* fsm); // Read buttons, add to que according to logic
void fsm_execute_state_function(fsm* fsm); // Choose correct state function

void fsm_expedite_orders_at_floor(fsm* fsm, int floor);

// The following functions are used to determine how to transition from the state
void fsm_resting(fsm* fsm);
void fsm_moving(fsm* fsm);