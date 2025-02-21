#include "que.h"
#include "elevio.h"

typedef enum {
    IDLE = 0,
    WAITING = 1,
    MOVING = 2,
    REACHED_FLOOR = 3,
} States;

typedef enum {
    OPEN = 0,
    CLOSED = 1,
} DoorStates;

typedef struct fsm {
    States state;
    MotorDirection dir;
    DoorStates door;
    int waiting;
    Node* head;
} fsm;

void fsm_init();

void fsm_take_orders(fsm* fsm); // Read buttons, add to que according to logic
void fsm_execute_state_function(fsm* fsm); // Choose correct state function

// The following functions are used to determine how to transition from the state
void fsm_idle(fsm* fsm);
void fsm_waiting(fsm* fsm);
void fsm_moving(fsm* fsm);
void fsm_reached_floor(fsm* fsm);