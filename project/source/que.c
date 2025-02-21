#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "que.h"

Node* create_node(int floor, MotorDirection dir)
{
    // Allocate the new node_p
    Node* node_p = (Node*)malloc(sizeof(Node));
    if (node_p == NULL)
    {
        perror("Memory allocation failed!\n");
    }
    // Init the new node_p
    node_p->parent_p = NULL;
    node_p->child_p = NULL;
    node_p->floor = floor;
    node_p->dir = dir;

    return node_p;
}

Node* que_get_tail_node_p(Node** head_pp)
{
    // The que is empty if head_pp points to NULL
    if (*head_pp == NULL) return *head_pp;

    // Find the tail Node by locating the node_p without a child
    Node* tail_p = *head_pp;
    while (1)
    {
        if(tail_p->child_p == NULL)
        {
            return tail_p;
        }
        else
        {
            tail_p = tail_p->child_p;
        }
    }
}


Node* que_add_node_back(Node** head_pp, int floor, MotorDirection dir)
{
    Node* new_node_p = create_node(floor, dir);
    
    if (*head_pp == NULL)
    {
        // The que is empty, make head_pp point to the new node_p
        *head_pp = new_node_p;
    }
    else 
    {
        Node* tail_p = que_get_tail_node_p(head_pp);
    
        // The new node_p is the tail
        tail_p->child_p = new_node_p;
        new_node_p->parent_p = tail_p;
    }
    return new_node_p;
}

void que_delete_node(Node** head_pp, Node* node_p)
{
    // The que is empty, nothing to delete
    if (node_p == NULL) return;

    if (node_p->parent_p == NULL)
    {
        // We want to delete the head_pp in a non empty que
        if (node_p->child_p != NULL)
        {
            // Assign the new head_p
            *head_pp = node_p->child_p;
            (*head_pp)->parent_p = NULL;
        }
        else
        {
            // There is no new head_pp to appoint
            *head_pp = NULL;
        }
    
    }
    else
    {
        // Update linked list by linking the parent and child of the node
        // we are deleting  
        node_p->parent_p->child_p = node_p->child_p;
        // The node we are deleting might be the tail, meaning it does not
        // have a child.
        if (node_p->child_p != NULL){
            node_p->child_p->parent_p = node_p->parent_p;

        }
    }
    
    free(node_p);
}

void que_delete(Node** head_pp)
{
    Node* tail_p = que_get_tail_node_p(head_pp);

    // The que is already empty, no need to delete any nodes
    if (tail_p == NULL) return;

    while(tail_p->parent_p != NULL)
    {
        // Save the parent of the tail, which will be the new tail
        Node* new_tail_p = tail_p->parent_p;
        que_delete_node(head_pp, tail_p);
        // Assign the tail to be the parent of the old tail
        tail_p = new_tail_p;
    }

    // Free head node
    que_delete_node(head_pp, *head_pp);
}

void print_que_forward(Node** head_pp) {
    Node* temp_p = *head_pp;
    // There is nothing to print in an empty que
    if (*head_pp == NULL) printf("Empty");

    int first_node = 1;

    while (temp_p != NULL)
    {
        printf(first_node ? "" : "<->");
        first_node = 0;
        printf("(floor: %i, dir: %i)", temp_p->floor, temp_p->dir);
        temp_p = temp_p->child_p;
    }
    printf("\n");
}

void que_delete_requests_at_floor(Node** head_pp, int floor)
{
    if (*head_pp == NULL) return;
    // Traverse list from the front
    Node* current_node = *head_pp;
    while (current_node != NULL)
    {
        if (current_node->floor == floor)
        {
            current_node = current_node->child_p;
            que_delete_node(head_pp, current_node->parent_p);
        }
        else
        {
            current_node = current_node->child_p;
        }
    }
}

/**
 * @ret: 1 if the que is empty, else 0
 */
int que_is_empty(Node** head_pp)
{
    return (head_pp == NULL) ? 1 : 0;
}

void que_is_orders_at_floor_in_dir(Node** head_pp, int floor, MotorDirection dir)
{
    if (*head_pp == NULL) return;
    Node* current_node = *head_pp;
    // Traverse list from the front
    while (current_node != NULL)
    {
        if ((current_node->floor == floor) & (current_node->dir == dir))
        {
            return;
        }
        current_node = current_node->child_p;
    }
}

MotorDirection trip_direction(int floor, ButtonType button) {
    int current_floor = elevio_floorSensor();
    int called_floor = elevio_callButton(floor,button);
    
    if(current_floor>called_floor) {
        return DIRN_DOWN;
    } else if (current_floor<called_floor) {
        return DIRN_UP;
    } else {
        return DIRN_STOP;
    }
}