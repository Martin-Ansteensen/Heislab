#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include "driver/elevio.h"
#include "fsm.h"
#include "que.h"

int main()
{
    Node* que_head = NULL;
    fsm fsm;
    fsm.state = UNDEFINED;
    fsm.dir = DIRN_STOP;
    fsm.door = CLOSED;
    fsm.waiting_to_close_door = 0;
    fsm.head = &que_head;
    elevio_init();
    fsm_init(&fsm);
    while (1)
    {
        // Debugging
        printf("s: %i \t, f: %i \t d:%i \t q:", fsm.state, fsm.floor, fsm.dir);
        print_que_forward(fsm.head);

        fsm_take_orders(&fsm);
        fsm_execute_state_function(&fsm);
    }
    que_delete(&que_head);
    return 0;
}
