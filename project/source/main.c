#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include "driver/elevio.h"
#include "fsm.h"
#include "que.h"

int main(){

    Node* que_head = NULL;
    fsm fsm;
    fsm.state = UNDEFINED;
    fsm.dir = DIRN_STOP;
    fsm.door = CLOSED;
    fsm.waiting = 0;
    fsm.head = &que_head;
    elevio_init();
    fsm_init(&fsm);

    return 0;
}
