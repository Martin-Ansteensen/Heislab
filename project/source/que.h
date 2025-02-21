#pragma once
#include "driver/elevio.h"

typedef struct Node {
    struct Node* parent_p;
    struct Node* child_p;
    int floor;
    MotorDirection dir;
} Node;


Node* create_node(int floor, MotorDirection dir);
Node* que_get_tail_node_p(Node** head_pp);
Node* que_add_node_back(Node** head_pp, int floor, MotorDirection dir);
void que_delete_node(Node** head_pp, Node* node_p);
void que_delete(Node** head_pp);
void print_que_forward(Node** head_pp);

void que_delete_requests_for_floor(Node** head_pp, int floor);
int que_is_empty(Node** head_pp);
int que_is_orders_at_floor_in_dir(Node** head_pp, int floor, MotorDirection dir);
int que_is_orders_in_dir(Node** head_pp, int floor, MotorDirection dir);
