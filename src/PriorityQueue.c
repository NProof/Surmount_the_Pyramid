#include "../header/PriorityQueue.h"
#include "../header/Maze.h"

void push(PQnode ** head, struct listNode * d, int p) {
    PQnode* start = (*head);

    // Create new PQnode
    PQnode* temp = newNode(d, p);

    // Special Case: The head of list has lesser
    // priority than new node. So insert new
    // node before head node and change head node.
    if ((*head)->priority > p) {

        // Insert New PQnode before head
        temp->next = *head;
        (*head) = temp;
    }
    else {

        // Traverse the list and find a
        // position to insert new node
        while (start->next != NULL &&
               start->next->priority < p) {
            start = start->next;
        }

        // Either at the ends of the list
        // or at required position
        temp->next = start->next;
        start->next = temp;
    }
}

PQnode * newNode(struct listNode * d, int p)
{
    PQnode * temp = (PQnode *)malloc(sizeof(PQnode));
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;

    return temp;
}

struct listNode * peek(PQnode ** head) {
    return (*head)->data;
}

void pop(PQnode ** head) {
    PQnode * temp = *head;
    (*head) = (*head)->next;
    free(temp);
}

int isEmpty(PQnode ** head) {
    return (*head) == NULL;
}
