#pragma once
#include "driver/elevio.h"
#include "timer.h"

/**
* @file
* @brief A module implementing a general linked list with extra functionality
* related to the specific needs for a que of elevator orders.
*/

/**
 * @brief Struct for a node element in a linked list. Each @c Node is
 * an order for the elevator.
 */
typedef struct Node {
    struct Node* parent_p;  /**< Pointer to the @c Node before in the linked list. If no such element exist, it is @c NULL (and the @c Node is the head). */
    struct Node* child_p;   /**< Pointer to the @c Node after in the linked list. If no such element exist, it is @c NULL (and the @c Node is the tail). */
    int floor;              /**< The floor of the order. */
    MotorDirection dir;     /**< The direction of the order. Direction is based on the type of button pressed.*/
} Node;


/**
 * @brief Allocate and initialize a node on the heap.
 * 
 * @param[in] floor Floor of the order.
 * @param[in] dir Direction of the order. Direction is based on the type of button pressed.
 * 
 * @return A pointer to the @c Node created on the heap.
 */
Node* create_node(int floor, MotorDirection dir);


/**
 * @brief Get the pointer to the last @c Node in the linked-list (the tail).
 * 
 * @param[in] head_pp Double pointer to the first @c Node (head) in the linked-list.
 * 
 * @return A pointer to the tail @c Node.
 */
Node* que_get_tail_node_p(Node** head_pp);


/**
 * @brief Add a new @c Node to the list by inserting it in the back,
 * making it the tail.
 * 
 * @param[in, out] head_pp Double pointer to the first @c Node (head) in the
 * list. If the list was previosly empty, meaning @c head_pp pointed to
 * @c NULL, it will now point to the new @c Node.
 * @param[in] floor Floor of the order.
 * @param[in] dir Direction of the order. Direction is based on the type of button pressed.
 * 
 * @return A pointer to the the new @c Node.
 */
Node* que_add_node_back(Node** head_pp, int floor, MotorDirection dir);


/**
 * @brief Remove the @c Node from the list by linking the element
 * before (parent) and after (child). Remove the node from the heap.
 *
 * @param[in, out] head_pp Double pointer to the first element (head) in the list.
 * If we want to delete the head, @c head_pp will be changed to point the the child of the head. 
 * @param[in] node_p Pointer to the @c Node we want to delete.
 */
void que_delete_node(Node** head_pp, Node* node_p);


/**
 * @brief Delete the whole list (free it from the heap) recursivley,
 * beginning with the tail.
 *
 * @param[in] head_pp Double pointer to the first @c Node (head) in the list.
 */
void que_delete(Node** head_pp);


/**
 * @brief Print the list to the terminal beginning with the head. Made for
 * debugging purposes
 *
 * @param[in] head_pp Double pointer to the first @c Node (head) in the list.
 */
void print_que_forward(Node** head_pp);


/**
 * @brief Delete all @c Node with the specified floor.
 *
 * @param[in] head_pp Double pointer to the first @c Node (head) in the list.
 * @param[in] floor 
 */
void que_delete_orders_for_floor(Node** head_pp, int floor);


/**
 * @brief Check if list is empty
 *
 * @param[in] head_pp Double pointer to the first @c Node (head) in the list.
 * 
 * @return 1 if the list is empty else 0.
 */
int que_is_empty(Node** head_pp);


/**
 * @brief Check if there are any orders for a given floor in the specified direction. This
 * includes cab orders (inside elevator) for that floor, and up/down orders at the floor.
 *
 * @param[in] head_pp Double pointer to the first @c Node (head) in the list.
 * @param[in] floor The floor we want to check for orders.
 * @param[in] dir The direction we want the orders to be in.

 * @return 1 if there are orders for the floor in the wanted direction, else 0.
 */
int que_is_orders_for_floor_in_dir(Node** head_pp, int floor, MotorDirection dir);


/**
 * @brief Check if there are any orders past the specified floor in the specified direction.
 *
 * @param[in] head_pp Double pointer to the first @c Node (head) in the list.
 * @param[in] floor We check floors after this floor for orders (in the specified direction).
 * @param[in] dir The direction we want to check for orders (before/after the specified floor).

 * @return 1 if there are orders in the direction, else 0.
 */
int que_is_orders_in_dir(Node** head_pp, int floor, MotorDirection dir);
