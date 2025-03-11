#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "timer.h"
#include "driver/elevio.h"
#include "fsm.h"
#include "que.h"

int main()
{
    Node* que_head = NULL;
    fsm fsm;
    fsm.state = UNDEFINED;
    fsm.dir = DIRN_STOP;
    fsm.door_open = 0;
    fsm.head = &que_head;
    elevio_init();
    fsm_init(&fsm);
    while (1)
    {
        // Debugging
        printf("s: %i \t, f: %i \t d:%i \t q:", fsm.state, fsm.floor, fsm.dir);
        print_que_forward(fsm.head);

        elevio_stopLamp(elevio_stopButton());
        if(elevio_stopButton())
        {
            que_delete(&que_head);
            elevio_motorDirection(DIRN_STOP);
            fsm.state = RESTING;
            for(int i = 0; i<N_FLOORS; i++) {
                elevio_buttonLamp(i, BUTTON_CAB, 0);
                elevio_buttonLamp(i, BUTTON_HALL_DOWN, 0);
                elevio_buttonLamp(i, BUTTON_HALL_UP, 0);
            }
            if(elevio_floorSensor() !=-1) {
                timer_start();
                elevio_doorOpenLamp(1);
                fsm.door_open = 1;
            }
        continue;
        }   

        fsm_take_orders(&fsm);
        fsm_execute_state_function(&fsm);
    }
    que_delete(&que_head);
    return 0;
}
