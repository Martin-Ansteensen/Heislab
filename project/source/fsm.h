#pragma once
#include "que.h"
#include "driver/elevio.h"
#include "timer.h"

/**
* @file
* @brief A module implementing a finite state machine for handling the operation
* of an elevator.
*/

/**
 * @brief Enum to easily identify the state of the fsm.
 */
typedef enum {
    UNDEFINED = -1,
    RESTING = 1,
    MOVING = 2
} States;


/**
 * @brief Struct for the fsm. In addition to its state it has a number
 * of internal variables.
 */
typedef struct {
    States state; /**< The state of the fsm*/
    MotorDirection dir; /**< The direction the elevator is moving in*/
    int door_open; /**< 1 for open door, 0 for closed*/
    Node** head; /**< Double pointer to the first element in the que of orders*/
    int floor; /**< The last floor the elevator was at*/
} fsm;

/**
 * @brief Initialize the elevator making sure it obtains a valid state. This is done by driving
 * downwards until a floor is reached, and then setting the state of the fsm. All button lamps
 * are turned off.
 * 
 * @param[in] fsm Pointer to the fsm struct.
 */
void fsm_init(fsm* fsm);


/**
 * @brief Read each button, if a button is pressed light it up and add an order to the que.
 * 
 * @param[in] fsm Pointer to the fsm struct.
 */
void fsm_take_orders(fsm* fsm);

/**
 * @brief Execute the correct state function based on the fsm's current state.
 * 
 * @param[in] fsm Pointer to the fsm struct.
 */
void fsm_execute_state_function(fsm* fsm); // Choose correct state function

/**
 * @brief Expedite the ordres in at the floor by opening the door and starting the timer,
 * turning off all order buttons for that floor and removing all orders for that floor.
 * 
 * @param[in] fsm Pointer to the fsm struct.
 */
void fsm_expedite_orders_at_floor(fsm* fsm, int floor);

/**
 * @brief Logic covering all possible actions when in the resting state.
 * @param[in] fsm Pointer to the fsm struct.
 */
void fsm_resting(fsm* fsm);

/**
 * @brief Logic covering all possible actions when in the moving state.
 * @param[in] fsm Pointer to the fsm struct.
 */
void fsm_moving(fsm* fsm);