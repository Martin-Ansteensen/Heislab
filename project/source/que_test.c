#include <stdlib.h>
#include <stdio.h>

#include "que.h"
int main()
{
    Node* que_head = NULL;
    for (int i=0; i<1; i++)
    {
        int N = 7;        
        printf("Add %i nodes with increasing floor\n", N);
        printf("&head         , &node\n");
        for (int i=1; i <= N; i++)
        {
            Node* n = que_add_node_back(&que_head, i, DIRN_UP);
            printf("%p, %p\n", que_head, n);
        }

        printf("\nFinal que\n");
        print_que_forward(&que_head);

        printf("\nDelete the head\n");
        que_delete_node(&que_head, que_head);
        print_que_forward(&que_head);

        printf("\nDelete the tail\n");
        que_delete_node(&que_head, que_get_tail_node_p(&que_head));
        print_que_forward(&que_head);

        printf("\nDelete the parent of the tail\n");
        que_delete_node(&que_head, que_get_tail_node_p(&que_head)->parent_p);
        print_que_forward(&que_head);

        printf("\nDelete the whole que\n");
        que_delete(&que_head);
        print_que_forward(&que_head);

    }
    return 0;
}